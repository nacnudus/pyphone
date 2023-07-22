# Pyphone

A very incomplete pyphon wrapper of Google's
[libphonenumber](https://github.com/google/libphonenumber/).  It isn't even
packaged as a python package.

I did this as a quick experiment to see whether it would be quicker than the
pure-python port https://github.com/daviddrysdale/python-phonenumbers.  For what
I was doing (extracting phone numbers from website pages of GOV.UK in bulk), it
was exactly the same speed.

## Requirements

Install libphonenumber in your system.  For example, using Arch Linux:

```sh
sudo
pacman -S libphonenumber
```

Install `pybind11`:

```sh
python -m ensurepip
python -m pip install -r requirements.txt
```

## Build

```sh
make
```

## Usage

```py
import pyphone
pnu = pyphone.PhoneNumberUtil()
pnm = pyphone.PhoneNumberMatcher(
    pnu,
    'My phone number is 0123456789.',
    'GB',
    pyphone.PhoneNumberMatcher.Leniency.POSSIBLE
)
match = pyphone.PhoneNumberMatch()
number_format = pyphone.PhoneNumberUtil.PhoneNumberFormat.E164

while pnm.HasNext():
    pnm.Next(match)
    print(pnu.Format(match.number(), number_format))
```
