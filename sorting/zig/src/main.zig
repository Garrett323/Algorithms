const std = @import("std");

var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = gpa.allocator();

pub fn main() !void {
    const arr = make_random_list(5);
    defer allocator.free(arr);
    std.debug.print("Unsorted:\n", .{});
    display(arr);
    merge_sort(arr);
    std.debug.print("Sorted:\n", .{});
    display(arr);
}

pub fn display(arr: []u8) void {
    for (0..arr.len - 1) |i| {
        std.debug.print("{}, ", .{arr[i]});
    }
    std.debug.print("{}\n", .{arr[arr.len - 1]});
}

pub fn make_random_list(length: u8) []u8 {
    const rng = std.crypto.random;
    const arr: []u8 = allocator.alloc(u8, length) catch unreachable;
    for (0..length) |i| {
        arr[i] = rng.int(u8);
    }
    return arr;
}

pub fn merge_sort(arr: []u8) void {
    if (arr.len <= 1) {
        return;
    }
    const left = arr[0 .. (arr.len + 1) / 2];
    merge_sort(left);
    const right = arr[(arr.len + 1) / 2 .. arr.len];
    merge_sort(right);
    merge(arr, right);
}

pub fn merge(left: []u8, right: []u8) void {
    const merged: []u8 = allocator.alloc(u8, left.len) catch unreachable;
    defer allocator.free(merged);
    var i: u16 = 0;
    var j: u16 = 0;
    for (0..left.len) |k| {
        if ((j >= right.len) or (i < (left.len + 1) / 2 and left[i] < right[j])) {
            merged[k] = left[i];
            i += 1;
        } else {
            merged[k] = right[j];
            j += 1;
        }
    }
    for (0..left.len) |k| {
        left[k] = merged[k];
    }
}

test "simple test" {
    var list = std.ArrayList(i32).init(std.testing.allocator);
    defer list.deinit(); // try commenting this out and see if zig detects the memory leak!
    try list.append(42);
    try std.testing.expectEqual(@as(i32, 42), list.pop());
}
