# Key-Value Store System in C

## Overview

This is a simple Key-Value Store implemented in C that allows the user to store, retrieve, delete, and manage key-value pairs. The key-value pairs are stored in memory and are persisted to a file (`database.txt`) so that data is not lost between program executions.

## Features

- **Put (p)**: Adds or updates a key-value pair.
- **Get (g)**: Retrieves the value associated with a given key.
- **Delete (d)**: Removes a key-value pair.
- **Clear (c)**: Clears all key-value pairs from the database.
- **Print All (a)**: Displays all key-value pairs in the database.

## File Structure

- `database.txt`: A plain text file used to store key-value pairs. Each line contains a key and its associated value in the format `key,value`.

## Compilation

To compile the project, you can use the following command:

```bash
gcc -o kvstore kvstore.c
```

## Usage

Once compiled, you can run the program with a series of commands. The program accepts commands through the command-line arguments. Below are the available commands:

- `p,key,value`: Add or update the key-value pair.
- `g,key`: Get the value for a given key.
- `d,key`: Delete a key-value pair.
- `c`: Clear all key-value pairs.
- `a`: Print all key-value pairs.

### Example Usage

```bash
./kvstore p,1,Hello    # Adds key 1 with value "Hello"
./kvstore p,2,World    # Adds key 2 with value "World"
./kvstore g,1          # Retrieves value for key 1 ("Hello")
./kvstore d,2          # Deletes key 2
./kvstore a            # Prints all key-value pairs
./kvstore c            # Clears all key-value pairs
```

### Command-line Arguments Example

```bash
./kvstore p,3,Goodbye p,4,Example g,3 a d,4 c
```

This will:
- Add the key-value pairs `(3, Goodbye)` and `(4, Example)`
- Retrieve the value for key `3` (`Goodbye`)
- Print all key-value pairs
- Delete the key-value pair with key `4`
- Clear all the key-value pairs

## File Format

The `database.txt` file is a simple text file where each line follows this format:

```
key,value
```

Example:

```
1,Hello
2,World
```

## Functions

### `put(KVPair **head, int key, const char *value)`
Adds a new key-value pair or updates the value of an existing key.

### `get(KVPair *head, int key)`
Retrieves the value for a given key.

### `delete(KVPair **head, int key)`
Deletes a key-value pair based on the key.

### `clear(KVPair **head)`
Clears all key-value pairs in the database.

### `loadDatabase(KVPair **head)`
Loads key-value pairs from the `database.txt` file into memory.

### `saveDatabase(KVPair *head)`
Saves all key-value pairs from memory to the `database.txt` file.

### `printAll(KVPair *head)`
Prints all key-value pairs stored in the database.

## Error Handling

- If the program cannot open `database.txt`, it will display an error message.
- If a key is not found when attempting to `get` or `delete`, it will notify the user.
