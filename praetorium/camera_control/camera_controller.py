from getpass import getpass
from pytapo import Tapo

ip = input("Adresse IP : ")
password = getpass("Mot de passe du compte TP-Link / Tapo : ")

print("Connexion à la caméra...")

camera = Tapo(ip, "admin", password)

print("Connexion réussie !")
print(camera.getBasicInfo())
print(camera.getPrivacyMode())
