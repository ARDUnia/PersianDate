# Changelog

All notable changes to the PersianDate library are documented in this file.

## [2.1.2] - 2026-09-18

### Fixed

* Corrected Gregorian-to-Persian conversion around Nowruz boundaries
* Corrected Persian-to-Gregorian reverse conversion
* Corrected Persian leap-year detection using the 33-year cycle
* Corrected weekday calculation and Friday holiday detection
* Added validation for invalid Gregorian and Persian dates
* Preserved the original lightweight Milaninia day-of-year algorithm

### Added

* Native automated tests for known dates, Nowruz boundaries, leap years, weekdays, holidays, invalid dates, and round-trip conversions
* GitHub Actions workflows for native tests and Arduino compilation
* Full-range validation for every Gregorian date from 2000-01-01 through 2100-12-31
* Hardware validation on Arduino Uno: 74,096 checks completed with zero failures

## [2.1.1]

* Added official Iranian fixed-holiday detection
* Added Friday holiday detection

## [2.0.0]

* Removed the RTClib dependency
* Added Persian-to-Gregorian conversion
* Added static conversion functions

## [1.1.0]

* First public release with RTClib dependency
