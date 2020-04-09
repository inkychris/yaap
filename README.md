# YAAP - Yet Another Argument Parser
YAAP is yet another (unimaginatively named)
argument parsing library for C++.

## Design Specification
In no specific order,
this library intends to
provide the following features:

- nesting of sub-commands (git style)
- positional and named arguments
- multiple names for named arguments (-f/--full)
- optional or mandatory arguments
- default values
- built-in support for basic data types: string, int, float, bool, lists of...
- support for custom string parsing functions
- automatically generated help text
- customisable help text
- argument groups (for help text sections)
- concatination of short flags (-abc),
  provided none take a value
  except (optionally) the last one
- customisation of named argument prefix character
  (change or add additional)
