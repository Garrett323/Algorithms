use rand::Rng;

const MAX: u32 = 20000;

fn main() {
    test(merge_sort);
}

fn test(alg: fn(&Vec<i32>) -> Vec<i32>) {
    let mut rng = rand::thread_rng();
    let data: Vec<i32> = (0..MAX).map(|_| rng.gen::<i32>() % 100).collect();
    println!("Unsorted:\n{:?}", data);
    let start = std::time::Instant::now();
    let data = alg(&data);
    let duration = start.elapsed();
    println!("\nSorted:\n{:?}\nSorting took {:?}", data, duration);
}

fn merge_sort(array: &Vec<i32>) -> Vec<i32> {
    let n = array.len();
    match n {
        0 => return vec![],
        1 => return vec![array[0]],
        _ => {
            let left = merge_sort(&array[0..((n + 1) / 2)].to_vec());
            let right = merge_sort(&array[((n + 1) / 2)..n].to_vec());
            return merge(&left, &right);
        }
    }
}

fn merge(left: &Vec<i32>, right: &Vec<i32>) -> Vec<i32> {
    let (l, r) = (left.len(), right.len());
    let n = l + r;
    let mut merged: Vec<i32> = Vec::with_capacity(n);
    let (mut i, mut j) = (0, 0);
    for _ in 0..n {
        if j >= r || (i < l && left[i] < right[j]) {
            merged.push(left[i]);
            i += 1;
        } else {
            merged.push(right[j]);
            j += 1;
        }
    }
    merged
}
