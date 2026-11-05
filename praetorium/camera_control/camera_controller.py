
import os
import sys
from pathlib import Path

from dotenv import load_dotenv
from pytapo import Tapo


# Chargement du .env situé à la racine de Cerno Verdict
project_root = Path(__file__).resolve().parents[2]
load_dotenv(project_root / ".env")

ip = os.getenv("CERNO_CAMERA_IP")
username = os.getenv("CERNO_CAMERA_USERNAME")
password = os.getenv("CERNO_CAMERA_PASSWORD")

if not all([ip, username, password]):
    print("ERROR Configuration Tapo incomplete", flush=True)
    sys.exit(1)


try:
	print("Connexion à la caméra...", file=sys.stderr)

	camera = Tapo(ip, username, password)

	print("READY", flush=True)

	for line in sys.stdin:
		command = line.strip()

		if command == "PRIVACY_ON":
			camera.setPrivacyMode(True)
			camera.setLEDEnabled(False)

			status = camera.getPrivacyMode()

			if status["enabled"] == "on":
				print("OK PRIVACY_ON", flush=True)
			else:
				print("ERROR PRIVACY_ON", flush=True)

		elif command == "PRIVACY_OFF":
			camera.setPrivacyMode(False)
			camera.setLEDEnabled(True)

			status = camera.getPrivacyMode()

			if status["enabled"] == "off":
				print("OK PRIVACY_OFF", flush=True)
			else:
				print("ERROR PRIVACY_OFF", flush=True)

		elif command == "STATUS":
			status = camera.getPrivacyMode()
			print(f"STATUS {status['enabled']}", flush=True)

		elif command == "QUIT":
			break

		else:
			print("ERROR UNKNOWN_COMMAND", flush=True)

except Exception as error:
    print(f"ERROR {error}", file=sys.stderr, flush=True)
    sys.exit(1)

print("Arrêt du contrôleur caméra.", file=sys.stderr)
