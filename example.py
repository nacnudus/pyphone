import pyphone
pnu = pyphone.PhoneNumberUtil()
pnm = pyphone.PhoneNumberMatcher(
    pnu,
    'My phone number is 0123456789',
    'GB',
    pyphone.PhoneNumberMatcher.Leniency.POSSIBLE
)
match = pyphone.PhoneNumberMatch()
number_format = pyphone.PhoneNumberUtil.PhoneNumberFormat.E164

while pnm.HasNext():
    pnm.Next(match)
    print(pnu.Format(match.number(), number_format))
