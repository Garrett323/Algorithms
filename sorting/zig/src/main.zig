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

    const arr2 = make_random_list(5);
    defer allocator.free(arr2);
    std.debug.print("\nQuickSort\nUnsorted:\n", .{});
    display(arr2);
    quick_sort(arr2);
    std.debug.print("Sorted:\n", .{});
    display(arr2);
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
    var i: usize = 0;
    var j: usize = 0;
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

pub fn swap(i: usize, j: usize, arr: []u8) void {
    const temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

pub fn quick_sort(arr: []u8) void {
    if (arr.len <= 1) {
        return;
    }
    const pivot = arr[0];
    var lesser: usize = 1;
    var equal: usize = 0;
    for (1..arr.len) |i| {
        if (arr[i] < pivot) {
            swap(i, lesser, arr);
            lesser += 1;
        } else if (arr[i] == pivot) {
            equal += 1;
        }
    }
    swap(0, lesser - 1, arr);
    quick_sort(arr[0 .. lesser - 1]);
    quick_sort(arr[lesser + equal .. arr.len]);
}

test "test merge sort" {
    var unsorted = [_]u8{ 5, 3, 29, 17, 0 };
    const sorted = [_]u8{ 0, 3, 5, 17, 29 };
    merge_sort(&unsorted);
    for (0..sorted.len) |i| {
        std.debug.assert(sorted[i] == unsorted[i]);
    }
    std.debug.print("MergeSort successfully tested on an array of length 5!\n", .{});
}

test "test quick sort" {
    var unsorted = [_]u8{ 5, 3, 29, 17, 0 };
    const sorted = [_]u8{ 0, 3, 5, 17, 29 };
    quick_sort(&unsorted);
    for (0..sorted.len) |i| {
        std.debug.assert(sorted[i] == unsorted[i]);
    }
    std.debug.print("QuickSort successfully tested on an array of length 5!\n", .{});
}
