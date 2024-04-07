use rand::Rng;

const MAX: i32 = 100;

fn make_random_vec(n: u32) -> Vec<i32> {
    let mut rng = rand::thread_rng();
    (0..n).map(|_| rng.gen::<i32>() % MAX).collect()
}

fn main() {
    let array = make_random_vec(20);
    println!("Unsorted:\n{:?}", array);
    let sorted = sort_and_count_inversions(&array);
    println!(
        "Sorted:\n{:?}\nNumber of inversions: {}",
        sorted.1, sorted.0
    );
}

fn sort_and_count_inversions(array: &Vec<i32>) -> (i32, Vec<i32>) {
    let n = array.len();
    if n <= 1 {
        return (0, array.clone());
    }
    let left = sort_and_count_inversions(&array[0..n / 2].to_vec());
    let right = sort_and_count_inversions(&array[n / 2..n].to_vec());
    let split = merge_and_count_split_inv(&left.1, &right.1);
    (left.0 + right.0 + split.0, split.1)
}

fn merge_and_count_split_inv(left: &Vec<i32>, right: &Vec<i32>) -> (i32, Vec<i32>) {
    let n = left.len() + right.len();
    let mut merged = Vec::<i32>::with_capacity(n);
    let (mut i, mut j) = (0, 0);
    let mut inverions = 0;
    for _ in 0..n {
        if j >= right.len() || (i < left.len() && left[i] <= right[j]) {
            merged.push(left[i]);
            i += 1;
        } else {
            merged.push(right[j]);
            j += 1;
            inverions += (n / 2 - i) as i32;
        }
    }
    (inverions, merged)
}
