# Terminal Chat Room

This project is a terminal-based chat room application written in C. The primary purpose of creating this application is to understand and practice network programming concepts.

## Features

- Multiple clients can connect to the chat room.
- Roles: Moderator, User.
  - Moderators can create, destroy chat rooms.
  - Users can join, leave chat rooms.
- Real-time message broadcasting to all connected clients.

## Requirements

- GCC compiler
- POSIX compliant operating system (Linux, macOS)

## Installation

1. Clone the repository:

```sh
git clone https://github.com/abdullahamin231/terminal-chat.git
```

2. Navigate to the project directory:

```sh
cd terminal-chat
```

3. Compile the server and client:

```sh
gcc -o server server.c
gcc -o client client.c
```

## Usage

1. Start the server:

```sh
./server
```

2. Start the client(s):

```sh
./client
```

## Learning Objectives

- [ ] Understand the basics of socket programming.
- [ ] Learn how to create a server and client using sockets.
- [ ] Learn how to handle multiple clients using threads.

## Contributing

I'm not sure if there is much to contribute here, but if you have any suggestions or improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License.

## Acknowledgements

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
