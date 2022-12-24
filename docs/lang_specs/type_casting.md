# Type Casting

> Recommended Reading: types.md

Type casting is a complex process. The process follow slightly different steps depending on whether the source type and/or the desired type are intrinsic or not.

## Intrinsic to Intrinsic

When type casting from an intrinsic type to another intrinsic type, the process follows these steps:

1. Determine the bit formats for both types.
2. Transform from the source format to the desired format.

## Intrinsic to Derived

When type casting from an intrinsic type to a derived type, the process follows these steps:

1. Determine if a constructor for the desired type exist that has the signature `desired_type(source_type) -> desired_type`.
2. If such a constructor exists, invoke the constructor and pass the source variable as the argument.

## Derived to Derived

When type casting from an derived type to another derived type, the process is a follows:

1. Determine if a constructor for the desired type exist that has the signature `desired_type(source_type) -> desired_type`.
2. If such a constructor exists, invoke the constructor and pass the source variable as the argument.

## Derived to Intrinsic

When type casting from a derived type to an intrinsic type, the process follows these steps:

1. Determine if the source type has a special `__reduce` method that has a return type that matches the desired type.
2. If such a method exists, invoke it and pass the source variable as the argument.
