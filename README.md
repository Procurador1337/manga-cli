# manga-cli

A command-line manga reader. Search MangaDex, browse chapters, and read pages via mpv.

## Features

- Search manga by title using the MangaDex API
- Browse chapters with pagination
- Read pages in mpv, streamed directly with nothing saved to disk
- Prompt to continue to the next chapter after finishing one
- Chapter counts shown next to search results
- Handles empty search/chapter results without crashing

## How it works

manga-cli queries the MangaDex API for search results and chapter listings. When you select a chapter, it passes the page URLs to mpv, which streams and displays them. No manga pages are ever written to disk.

## Dependencies

- Qt6 (Core, Network modules)
- CMake (3.16 or newer)
- A C++17-compatible compiler
- mpv, installed and available on your PATH

On Linux:

```bash
# Debian/Ubuntu
sudo apt install qt6-base-dev mpv cmake build-essential

# Arch
sudo pacman -S qt6-base mpv cmake base-devel

# Fedora
sudo dnf install qt6-qtbase-devel mpv cmake gcc-c++
```

## Building

```bash
git clone https://github.com/Procurador1337/manga-cli.git
cd manga-cli
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

```bash
./manga-cli
```

Enter a manga title, pick a result, pick a chapter, and mpv will open with the pages. Use mpv's controls to move between pages:

- `>` next page
- `<` previous page
- `q` quit

After a chapter finishes, you'll be asked whether to continue to the next one.

## Credit

This tool uses the [MangaDex API](https://api.mangadex.org/docs/swagger.html) to search for and retrieve manga information and chapter pages. All manga content, chapter translations, and page images are hosted and provided by MangaDex and the scanlation groups who uploaded them. manga-cli does not host, store, or modify any manga content itself — it only queries the API and displays what it returns.

Full credit for translations goes to the individual scanlation groups responsible for each chapter, as attributed by MangaDex.

## Disclaimer

manga-cli is an unofficial, third-party client and is not affiliated with, endorsed by, or sponsored by MangaDex. This tool is provided for personal, non-commercial use. All manga content accessed through this tool remains the property of its respective copyright holders (original authors/publishers), and translated chapters remain the property of their respective scanlation groups.

The developers of manga-cli are not responsible for how this tool is used, or for the availability, accuracy, or legality of content served by the MangaDex API. If you enjoy a series, please support the official release.
