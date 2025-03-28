Silence and Echo

Silence and Echo is a C++ program designed for testing and analyzing spoofed Denial-of-Service (DoS) attacks using malformed UDP packets. This tool allows users to simulate attack scenarios for cybersecurity research and defense testing purposes.

Features

Echo: Spoofs the last digits of your IP address, making it appear as if your network is under a DDoS attack.

Silence: Allows you to set a spoofed IP address, making the target system believe the attack originates from a third party.

Installation

Ensure you have the necessary dependencies installed before compiling and running the program.

1. Install Required Dependencies

sudo apt update && sudo apt install g++ nmap python3

2. Compile the C++ Files

g++ Echo.cpp -o Echo 
g++ SilenceC.cpp -o Silence

3. Run the Script

To start the simulation, execute the following command:

sudo python3 Silence.py

Usage

Echo will use your subnet (e.g., xxx.xxx.xxx.XXX) and spoof the last digits, making it seem like your system is being DDoSed.

Silence allows you to define a specific spoofed IP address, making the victim's system believe the attack is coming from that IP.

Platform Compatibility

This tool has been tested on:

Ubuntu

Kali Linux

It works on both Ethernet and WiFi networks.

Disclaimer

This tool is strictly for educational and cyber security research purposes. Unauthorized use of this tool to attack, disrupt, or mislead others is illegal and unethical. Use it responsibly and in compliance with all applicable laws.

Author

Made by Charles Mortensen. For more about the author, check out the article: https://thecyberexpress.com/utah-student-anti-phishing-vega/

License

This project is released under the MIT License.

