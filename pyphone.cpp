#include <pybind11/pybind11.h>

#include "phonenumbers/phonenumberutil.h"
#include "phonenumbers/phonenumbermatcher.h"
#include "phonenumbers/phonenumbermatch.h"

namespace py = pybind11;

using namespace std;
using namespace i18n::phonenumbers;

PYBIND11_MODULE(pyphone, m) {
    m.doc() = "libphonenumbers bindings"; // optional module docstring

    py::class_<PhoneNumberUtil> phone_number_util(m, "PhoneNumberUtil");

    // PhoneNumberUtil doesn't have a public constructor, because it is intended
    // to be a singleton.  Instead, it has a public method GetInstance that
    // only creates an instance if there isn't one, otherwise it returns the
    // existing instance.  We wrap that method as though it is a constructor.
    phone_number_util.def(py::init(&PhoneNumberUtil::GetInstance));

    py::enum_<PhoneNumberUtil::PhoneNumberFormat>(phone_number_util, "PhoneNumberFormat")
        .value("E164", PhoneNumberUtil::PhoneNumberFormat::E164)
        .value("INTERNATIONAL", PhoneNumberUtil::PhoneNumberFormat::INTERNATIONAL)
        .value("NATIONAL", PhoneNumberUtil::PhoneNumberFormat::NATIONAL)
        .value("RFC3966", PhoneNumberUtil::PhoneNumberFormat::RFC3966)
        .export_values();

    // The format function mutates a string that is passed in by reference, but
    // Python strings are immutable, so
    // we wrap the format function in a lambda function that creates such a
    // mutable string, passes it into the format function, and returns the
    // mutated string to Python.
    phone_number_util.def(
        "Format", [](const PhoneNumberUtil &self, const PhoneNumber &number,
                     PhoneNumberUtil::PhoneNumberFormat number_format) {
          string s;
          self.Format(number, number_format, &s);
          return s;
        });

    py::class_<PhoneNumberMatcher> phone_number_matcher(m, "PhoneNumberMatcher");

    phone_number_matcher.def(
        py::init<const PhoneNumberUtil &, const string &, const string &,
                 PhoneNumberMatcher::Leniency, int>(),
        py::arg("util"), py::arg("text"), py::arg("region_code"),
        py::arg("leniency"), py::arg("max_tries") = numeric_limits<int>::max());

    py::enum_<PhoneNumberMatcher::Leniency>(phone_number_matcher, "Leniency")
        .value("POSSIBLE", PhoneNumberMatcher::Leniency::POSSIBLE)
        .value("VALID", PhoneNumberMatcher::Leniency::VALID)
        .value("STRICT_GROUPING", PhoneNumberMatcher::Leniency::STRICT_GROUPING)
        .value("EXACT_GROUPING", PhoneNumberMatcher::Leniency::EXACT_GROUPING)
        .export_values();

    phone_number_matcher.def("HasNext", &PhoneNumberMatcher::HasNext);
    phone_number_matcher.def("Next", &PhoneNumberMatcher::Next);

    py::class_<PhoneNumber> phone_number(m, "PhoneNumber");

    py::class_<PhoneNumberMatch> phone_number_match(m, "PhoneNumberMatch");

    phone_number_match.def(py::init<int, const string &, const PhoneNumber &>(),
             py::arg("start"), py::arg("raw_string"), py::arg("number"))
        .def(py::init())
        .def("number", &PhoneNumberMatch::number);
  ;
}
