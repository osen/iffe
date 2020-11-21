Iffe
----
An object-oriented UI library for UNIX-like platforms.

Project Goals
-------------
- C89
- Object-oriented via MACROs
- Minimize dependencies
- Focus on maintainability
- Single static library
- Provide simple layout system and avoid tooling
- 100% memory safety in debug builds
  - Zero overhead for release builds
  - C++ weak_ptr clone
  - C++ vector clone

Out of Scope
------------
- Localization. US English only. Translation is best provided by screen scrapers
- GUI builders. Elegant API should render them unnecessary
- IPC, networking, etc. UI systems should only render UIs

