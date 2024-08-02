import asyncio
import message_pb2
import sys
from typing import Tuple

async def send_message() -> None:
    # Create a Person object and populate it
    person = message_pb2.Person()
    person.name = "John Doe"
    person.id = 1234
    person.email = "johndoe@example.com"

    # Serialize the object to a byte string
    serialized_data = person.SerializeToString()

    reader, writer = await asyncio.open_connection('127.0.0.1', 5005)

    print(f'Sending data to {writer.get_extra_info("peername")}')
    
    writer.write(serialized_data)
    await writer.drain()
    
    print('Data sent')

    writer.close()
    await writer.wait_closed()

async def periodic_send() -> None:
    while True:
        await send_message()
        await asyncio.sleep(1)

async def handle_client(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    data = await reader.read(1024)
    addr = writer.get_extra_info('peername')

    print(f"Connected by {addr}")

    # Deserialize the data
    person = message_pb2.Person()
    person.ParseFromString(data)

    # Print the structured data
    print("Received data:")
    print(f"Name: {person.name}")
    print(f"ID: {person.id}")
    print(f"Email: {person.email}")

    writer.close()
    await writer.wait_closed()

async def start_receiver() -> None:
    server = await asyncio.start_server(handle_client, '127.0.0.1', 5005)
    addr = server.sockets[0].getsockname()
    print(f'Serving on {addr}')

    async with server:
        await server.serve_forever()

async def main(role: str) -> None:
    if role == 'sender':
        await periodic_send()
    elif role == 'receiver':
        await start_receiver()
    else:
        print("Invalid argument: Use 'sender' or 'receiver'")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python communication.py <sender|receiver>")
    else:
        role = sys.argv[1]
        asyncio.run(main(role))
