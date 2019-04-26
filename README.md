# iNes Command Line Interface

## Usage

### Display ROM Informations

```sh
ines rom.nes
```

#### Example Output

```
Program ROM size: 128KB
Character ROM size: 0KB
Mapper: MMC1 (1)
Mirroring: horizontal
Battery-backed Save RAM: yes, size: 8KB
512 bytes Trainer: no
```

### Extract Program ROM

```sh
ines -e prg.out rom.nes
```

## Installation

```sh
git clone https://github.com/afrigon/ines-cli && cd ines-cli
make
```

This will build the binary into `./bin/ines`
