
#### Initialize project 

```bash
# new executable project
$ zig init-exe

# new library project
$ zig init-lib

# build executable
$ zig build

# run code file directly
$ zig run src/main.zig
```

```gitignore
zig-cache
zig-out
```


#### Hello world

```zig
const std = @import("std");

pub fn main() void {
    const name = "world";
    std.debug.print("Hello {s}\n", .{name});
}
```


#### Data types

```zig
// primitives 
var a: i32 = 10;
var b: f128 = 10.45;
var c: bool = true;

std.debug.print("{}, {}, {}\n", .{ a, b, c });
```

```zig
// arrays
const fixed_sized = [5]u8{ 10, 20, 30, 40, 50 };
std.debug.print("{}\n", .{fixed_sized.len});

// loop by value
for (fixed_sized) |n| {
    std.debug.print("{}\n", .{n});
}

// loop by reference
for (&fixed_sized) |*n| {
    std.debug.print("{}\n", .{n.*});
}

const variable_length = [_]i32{ 1, 2, 3, 4, 5, 6 };
for (variable_length, 0..) |n, index| {
  std.debug.print("{} - {}\n", .{ index, n });
}

// print for debug purposes
std.debug.print("{any}\n", .{variable_length});
```

TODO: strings, hash-maps


#### Switch 

```zig
test "switch" {
    var x: i8 = 10;

    const result = switch (x) {
        -1...1 => x * 2,
        10, 20 => x * 10,
        else => x,
    };

    try std.testing.expect(result == 100);
}
```


#### Pointers

```zig
var value: i32 = 10;
var ref: *i32 = &value;

// dereference pointer and mutate value
ref.* = 1000;

std.debug.print("memory address: {}\n", .{ref});
std.debug.print("derefenced value: {}\n", .{ref.*});
std.debug.print("value: {}\n", .{value});
```

```zig
// create pointer to non-const value
var value: i32 = 10;
const const_ref: *i32 = &value;
const const_ptr: *const i32 = &value;

// this will work because pointer itself is not const
const_ref.* = 1000;

// this will NOT work because the pointer is const    
const_ptr.* = 30000;
```



#### Functions

```zig
// convention is to use camel-case for function names
fn calculate(n: i32) i32 {
    return n * 10;
}

test "calculate" {
    const result = calculate(10);
    try std.testing.expect(@TypeOf(result) == i32);
    try std.testing.expect(result == 100);
}
```

```zig
// function arguments are constant by default
fn calculate(n: i32) void {
    // this will NOT compile
    n *= 10;
}
```

```zig
// pass pointer to function
fn calculate(n: *i32) void {
    n.* += 10;
}

test "calculate" {
    var value: i32 = 10;
    calculate(&value);
    try std.testing.expect(value == 20);
}
```

```zig
// pass a const pointer to function
fn calculate(n: *const i32) void {
    // this will NOT compile
    n.* += 10;
}
```



#### Defer

```zig
const expect = std.testing.expect;

test "defer" {
    var value: i32 = 10;
    {
        defer value += 5;
        try expect(value == 10);
    }

    try expect(value == 15);
}
```

```zig
test "defer" {
    var value: f32 = 5.0;
    {
        // defers will execute in reverse order
        defer value += 3;
        defer value /= 2;
    }

    try expect(value == 5.5);
}
```



#### Enums

```zig
const Direction = enum { NORTH, SOUTH, EAST, WEST };

test "enums" {
    const d = Direction.SOUTH;
    try expect(d == Direction.SOUTH);
}
```

```zig
// zero-indexed, can be cast to i32
const Direction = enum(i32) { NORTH, SOUTH, EAST, WEST };

test "enums" {
    const d = Direction.SOUTH;
    try expect(@intFromEnum(d) == 1);
}
```



#### Structs

```zig
const Vector2 = struct {
    x: f64,
    y: f64 = 0, // default field value

    fn swap(self: *Vector2) void {
        const tmp = self.x;
        self.x = self.y;
        self.y = tmp;
    }
};

test "structs" {
    var v = Vector2{
        .x = 10.0,
        .y = 30.5,
    };

    try expect(v.x == 10.0);

    // object must be mutable for this method call to work
    v.swap();
    try expect(v.x == 30.5);
}
```


#### Errors

```zig
// define error group
const IOError = error{
    PermissionDenied,
    NotFound,
};

test "errors" {
    const some_error: IOError!u8 = IOError.PermissionDenied;

    // handle error
    some_error catch |err| {
        try expect(err == IOError.PermissionDenied);

        switch (err) {
            IOError.PermissionDenied => print("error: permission denied", .{}),
            IOError.NotFound => print("error: file not found", .{}),
        }
    };

    const maybe_err: IOError!i32 = 300;
    // ignore error and use a default value
    const default_value = maybe_err catch 0;
    try expect(default_value == 300);
}
```

```zig
// function may return multiple types of errors
fn openFile(fileId: i32) !i32 {
    if (fileId == 10) {
        return IOError.PermissionDenied;
    }

    return fileId * 10;
}

pub fn main() void {
    const result = openFile(100) catch |err| {
        print("error was cought: {}\n", .{err});
        return;
    };

    print("{}\n", .{result == 1000});
}
```

```zig
// return specific type of error from function
fn openFile(fileId: i32) error{PermissionDenied}!i32 {
    if (fileId == 10) {
        return IOError.PermissionDenied;
    }

    return fileId * 10;
}
```

```zig
// return any error from an error group
fn openFile(fileId: i32) IOError!i32 {
    if (fileId == 10) {
        return IOError.PermissionDenied;
    }

    if (fileId == 20) {
        return IOError.NotFound;
    }

    return fileId * 10;
}

pub fn main() void {
    // handle multiple types of errors
    const result = openFile(10) catch |err| switch (err) {
        IOError.PermissionDenied => {
            print("error: denied\n", .{});
            return;
        },
        IOError.NotFound => {
            print("error: not found\n", .{});
            return;
        },
    };

    print("{}\n", .{result == 1000});
}
```