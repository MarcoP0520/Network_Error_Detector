import discord
import asyncio

TOKEN = "Bot_token"  # Replace with your actual bot token
CHANNEL_ID = 1336488379960786996  # Replace with your Discord channel ID

intents = discord.Intents.default()
client = discord.Client(intents=intents)

async def check_status():
    last_alert = None
    while True:
        try:
            print("📂 Checking if status.log exists...")

            with open("status.log", "r") as file:
                lines = file.readlines()

            if lines:
                last_status = lines[-1].strip()
                print(f"📜 Last line in status.log: {last_status}")

                if "Disconnected" in last_status and last_status != last_alert:
                    last_alert = last_status
                    channel = client.get_channel(CHANNEL_ID)

                    print(f"🚨 ALERT: Preparing to send: {last_status}")

                    if channel:
                        await channel.send(f"🚨 ALERT: {last_status}")
                        print(f"✅ Message sent: {last_status}")
                    else:
                        print("❌ ERROR: Channel not found!")

            await asyncio.sleep(30)  # Check every 30 seconds

        except Exception as e:
            print(f"❌ ERROR reading file: {e}")

@client.event
async def on_ready():
    print(f"✅ Logged in as {client.user}")
    client.loop.create_task(check_status())

client.run(TOKEN)
