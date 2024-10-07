import pyaudio
import pyttsx3
import datetime
import wikipedia
import pyjokes
import vlc_player_lib
from str_to_num import str_to_num
import math_module
import os

# Initialize PyAudio
p = pyaudio.PyAudio()

# List available audio devices (uncomment to use)
def list_audio_devices():
    info = p.get_host_api_info_by_index(0)
    numdevices = info.get('deviceCount')
    for i in range(numdevices):
        device = p.get_device_info_by_index(i)
        print(f"Device {i}: {device['name']}")

# Uncomment to list devices
# list_audio_devices()

# Set your secondary input and output device indices here
input_device_index = 1  # Change this to your input device index
output_device_index = 2  # Change this to your output device index

# Audio configuration
chunk = 1024
format = pyaudio.paInt16
channels = 1
rate = 16000

# Create input stream
input_stream = p.open(format=format, channels=channels, rate=rate, input=True,
                       frames_per_buffer=chunk, input_device_index=input_device_index)

# Create output stream
output_stream = p.open(format=format, channels=channels, rate=rate, output=True,
                        output_device_index=output_device_index)

# Initialize text-to-speech engine
engine = pyttsx3.init()

def talk(text):
    engine.say(text)
    engine.runAndWait()

def handle_command(text):
    text = text.lower()
    
    if 'who is ' in text:
        person = text.replace('who is ', '')
        return wikipedia.summary(person, 1)
    elif "what is " in text:
        query = text.replace('what is ', '')
        return wikipedia.summary(query, 1)
    elif 'play on youtube ' in text:
        song = text.replace('play on youtube ', '')
        pywhatkit.playonyt(song)
        return f'Playing {song}'
    elif 'time ' in text:
        return 'Current time is ' + datetime.datetime.now().strftime('%I:%M %p')
    elif 'date' in text:
        return 'Sorry, I have a headache'
    elif 'are you single' in text:
        return 'I am in a relationship with Wi-Fi'
    elif 'joke' in text:
        return pyjokes.get_joke()
    elif any(key in text for key in vlc_player_lib.action_dict.keys()):
        player_command = str_to_num(text)
        return vlc_player_lib.vlc_player(player_command)
    elif any(key in text for key in math_module.operators.keys()):
        equation = str_to_num(text)
        return math_module.math_module(equation)
    elif "abort process " in text:
        command = text.replace('abort process ', '')
        if command == "exit level one":
            quit()
        elif command == "exit level two":
            os.system("sudo reboot")
        elif command == "exit level three":
            os.system("sudo shutdown now")
    else:
        return 'Please say the command again'

def loop():
    data = input_stream.read(chunk)  # Capture audio data
    # Implement your speech recognition logic here to convert audio data to text
    text = ""  # Placeholder for recognized text

    if text.startswith("system command"):
        command_text = text.replace("system command ", "", 1)
        return handle_command(command_text)
    else:
        return 'Please say the command again'

if __name__ == '__main__':
    while True:
        try:
            output = loop()
            if output:
                print(output)
                talk(output)
                # Here you could generate or fetch audio data to play through the output device if needed
        except Exception as e:
            print(f"\033[31m--ERROR--\n{e}\033[0m")
