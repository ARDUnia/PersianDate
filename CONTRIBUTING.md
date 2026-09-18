# Contributing to PersianDate

Thank you for your interest in improving PersianDate. Bug reports, test cases, documentation improvements, and pull requests are welcome.

## Reporting a Bug

Before opening a new issue, please check the existing issues.

A useful bug report should include:

* Arduino board and architecture
* Arduino IDE or PlatformIO version
* PersianDate library version
* Input date
* Expected result
* Actual result
* Minimal example code, when possible

For conversion problems, please include both conversion directions and any relevant Nowruz or leap-year boundary information.

## Submitting a Pull Request

1. Fork the repository
2. Create a branch from `main`
3. Make one focused change
4. Add or update native tests when changing calendar logic
5. Confirm that the Arduino examples compile
6. Update the documentation when behavior or public APIs change
7. Open a pull request with a clear description of the change

Please preserve compatibility with Arduino AVR, ESP8266, and ESP32 platforms whenever possible.

## Validation

Pull requests are automatically checked by:

* Native calendar validation tests
* Arduino Uno compilation through GitHub Actions
* Known-date and round-trip conversion tests

Changes to calendar calculations should include tests for known dates, Nowruz boundaries, Persian leap years, weekdays, holidays, and reverse conversion.

## Code Style

* Keep the implementation lightweight and suitable for embedded systems
* Avoid unnecessary dynamic memory allocation
* Preserve the existing public API unless a breaking change is clearly justified
* Use clear names and comments for calendar calculations

## Security Issues

Please do not publish sensitive security details in a public issue. Follow the instructions in `SECURITY.md` when reporting a security concern.
