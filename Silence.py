import os
import subprocess


def MainMenu():
    os.system('clear')
    print("""
    ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
    ░░      ░░░        ░░  ░░░░░░░░        ░░   ░░░  ░░░      ░░░        ░
    ▒  ▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒    ▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒▒▒▒
    ▓▓      ▓▓▓▓▓▓  ▓▓▓▓▓  ▓▓▓▓▓▓▓▓      ▓▓▓▓  ▓  ▓  ▓▓  ▓▓▓▓▓▓▓▓      ▓▓▓
    ███████  █████  █████  ████████  ████████  ██    ██  ████  ██  ███████
    ██      ███        ██        ██        ██  ███   ███      ███        █
    ██████████████████████████████████████████████████████████████████████
    ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
    ░        ░░░      ░░░  ░░░░  ░░░      ░░
    ▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒
    ▓      ▓▓▓▓  ▓▓▓▓▓▓▓▓        ▓▓  ▓▓▓▓  ▓
    █  ████████  ████  ██  ████  ██  ████  █
    █        ███      ███  ████  ███      ██   
    ████████████████████████████████████████
    Author: Charles Mortensen
    """)
    print("1. Silence Attack")
    print("2. Echo Attack")
    print("3. Nmap CheatSheet")
    print("4. About Program")
    print("5. Clear Screen")





def code():
    MainMenu()
    while True:
        Amadeus = 0
        while Amadeus == 0:
            user_input = input(">>>:")
            
            if user_input.isdigit() or (user_input[0] == '-' and user_input[1:].isdigit()):
                choice = float(user_input)

                if choice == 1:
                    os.system('sudo ./Silence')
                    
                    
                    
                elif choice == 2: 
                    os.system('sudo ./Echo')


                
                elif choice == 3: 
                    os.system('clear')
                    Nmap_cheatsheet()


                elif choice == 4:
                    os.system('clear')
                    print("""
                    
                    
                    
Silence is a highly sophisticated DoS (Denial of Service) tool designed to send malformed packets to a target's computer in a way that makes it nearly impossible to trace the origin of the attack. Even experienced cybersecurity professionals would find it incredibly challenging to determine where these packets are coming from. The true brilliance of Silence lies in its ability to obscure its attack vector, leaving the target unaware of what is hitting them, while effectively overwhelming their system.
===================================================================================================================================================================
Echo, another creation by the renowned cybersecurity innovator Charles Mortensen, is an evolution of the DoS toolset. Much like Silence, Echo sends malformed packets to its victim's computer. However, Echo takes a different approach—it mimics a Distributed Denial of Service (DDoS) attack, making it appear as though multiple machines are attacking the target. In reality, it's a single computer conducting the attack. This deceptive behavior allows Echo to create chaos and confusion, masking its true nature and complicating any effort to defend against or trace the source.
=========================================================================================================================================================
Both Silence and Echo are the products of nearly a year of relentless development by Charles Mortensen, whose dedication to crafting next-level cybersecurity tools has made these tools a powerful asset in the arsenal of anyone looking to understand the complexities of digital warfare. The work he put in was not without challenges, but the end result has been worth every effort, as these tools redefine what it means to execute and counter sophisticated attacks.
                    """)
                
                
                elif choice == 5:
                    os.system('clear')
                    MainMenu()
                
            else:
                print("Invalid input")





network_scans = {
    '1': "Ping Scan (-sP): Discovers live hosts on a network",
    '2': "TCP SYN Scan (-sS): Performs a stealthy scan by sending SYN packets",
    '3': "TCP Connect Scan (-sT): Completes the TCP three-way handshake to establish a full connection",
    '4': "UDP Scan (-sU): Scans for open UDP ports",
    '5': "Service Version Detection (-sV): Determines service versions running on open ports",
    '6': "Operating System Detection (-O): Attempts to identify the operating system of the target",
    '7': "Comprehensive Port Scanning (-p-): Scans all 65,535 TCP ports on a target",
    '8': "Script Scanning (--script): Executes Nmap scripts for additional functionality like vulnerability detection",
    '9': "Aggressive Scan (-A): Enables OS detection, version detection, script scanning, and traceroute",
    '10': "ICMP Echo Ping (-PE): Sends ICMP echo requests to determine if hosts are up",
    '11': "TCP ACK Scan (-sA): Determines if ports are filtered by sending TCP ACK packets",
    '12': "Fragmentation Scan (-f): Evades packet filters by fragmenting packets",
    '13': "IP Protocol Scan (-sO): Determines which IP protocols are supported by target hosts",
    '14': "Idle Scan (-sI): Spoofs packets through an idle zombie host to scan a target",
    '15': "List Scan (-sL): Lists all IP addresses in a target network without sending packets",
    '16': "FTP Bounce Scan (-b): Bounces the scan off an FTP server to evade firewall restrictions",
    '17': "Reverse DNS Resolution (-n): Performs reverse DNS resolution to display hostnames instead of IP addresses",
    '18': "RPC Scan (-sR): Enumerates RPC services by performing portmapper queries",
    '19': "SCTP INIT Scan (-sY): Determines if SCTP endpoints are active by sending SCTP INIT packets",
    '20': "UDP Scan (IPv6) (-6 -sU): Scans for open UDP ports using IPv6",
    '21': "TCP SYN Scan (IPv6) (-6 -sS): Performs a stealthy scan using IPv6",
    '22': "Aggressive Scan (IPv6) (-6 -A): Enables aggressive scan using IPv6",
    '23': "SCTP INIT Scan (IPv6) (-6 -sY): Determines if SCTP endpoints are active using IPv6",
    '24': "FTP Bounce Scan (IPv6) (-6 -b): Bounces the scan off an FTP server using IPv6",
    '25': "Reverse DNS Resolution (IPv6) (-6 -n): Performs reverse DNS resolution using IPv6"
}



def perform_scan(command):
    try:
        print(f"{'='*40}\nExecuting Scan...\n{'='*40}")
        result = subprocess.run(command.split(), capture_output=True, text=True)
        print(f"{'='*40}\nScan Results:\n{'='*40}")
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"{'='*40}\nError: {e}\n{'='*40}")
    except Exception as e:
        print(f"{'='*40}\nAn unexpected error occurred: {e}\n{'='*40}")

def Nmap_cheatsheet():
    print(f"{'='*40}\nWelcome to Nmap Cheat Sheet!\n{'='*40}")
    print("Choose a scan option:")
    print(f"{'='*40}")
    
    for key, value in network_scans.items():
        print(f"{key}. {value}")
    
    print(f"{'='*40}")
    option = input("Enter your choice (number): ")
    target = input("Enter the IP/List of IPs: ")

    if option in network_scans:
        # Extract the scan flag from the description
        command_flag = network_scans[option].split(":")[0].strip()
        # Create the Nmap command
        command = f"nmap {command_flag} {target}"
        perform_scan(command)
    else:
        print(f"{'='*40}\nInvalid option. Please select a valid scan.\n{'='*40}")
        
        
        
# Example usage

code()
