import discord
import asyncio
import os

TOKEN = "bot token"  # Replace with your actual bot token
CHANNEL_ID = 1336488379960786996  # Replace with your Discord channel ID

intents = discord.Intents.default()
client = discord.Client(intents=intents)

async def tail_log():
    """ Continuously read new lines from status.log and send alerts """
    await asyncio.sleep(5)  # Small delay to ensure bot is ready

    try:
        with open("status.log", "r") as file:
            file.seek(0, os.SEEK_END)  # Move to the end of the file

            while True:
                line = file.readline()
                if not line:  # No new line found, wait and check again
                    await asyncio.sleep(0.1)
                    continue

                alert = line.strip()
                if alert:
                    channel = client.get_channel(CHANNEL_ID)
                    if channel:
                        await channel.send(f"🚨 ALERT: {alert}")
                        print(f"✅ Sent alert: {alert}")
                    else:
                        print("❌ ERROR: Channel not found!")

    except Exception as e:
        print(f"❌ ERROR reading file: {e}")

@client.event
async def on_ready():
    print(f"✅ Logged in as {client.user}")
    client.loop.create_task(tail_log())  # Start file monitoring task

client.run(TOKEN)
