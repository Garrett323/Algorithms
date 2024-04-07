use rand::Rng;

#[derive(Debug, Clone)]
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn new(x: i32, y: i32) -> Point {
        Point { x, y }
    }
}

fn make_random_points(n: usize) -> Vec<Point> {
    let mut rng = rand::thread_rng();
    const MAX_VAL: i32 = 20;
    (0..n)
        .map(|_| Point::new(rng.gen::<i32>() % MAX_VAL, rng.gen::<i32>() % MAX_VAL))
        .collect()
}

fn main() {
    let points = make_random_points(5);
    println!("{:?}", &points);
    println!(
        "Closest Pair by exhaustive_search: {:?}",
        exhaustive_search(&points)
    );
    println!(
        "Closest Pair by recursive algorithm: {:?}",
        find_closest_pair(points)
    );
}

fn find_closest_pair(points: Vec<Point>) -> (Point, Point) {
    let mut points_x = points.clone();
    let mut points_y = points.clone();
    points_x.sort_by(|a, b| a.x.cmp(&b.x));
    points_y.sort_by(|a, b| a.y.cmp(&b.y));
    find_closest_pair_rec(points_x, points_y)
}

fn find_closest_pair_rec(points_x: Vec<Point>, points_y: Vec<Point>) -> (Point, Point) {
    let n = points_x.len();
    if n <= 3 {
        return exhaustive_search(&points_x);
    }
    let left_x = points_x[0..n / 2].to_vec().clone();
    let right_x = points_x[n / 2..n].to_vec().clone();
    let left_y: Vec<Point> = points_y
        .iter()
        .filter(|p| p.x <= left_x.last().unwrap().x)
        .map(|p| p.clone())
        .collect();
    let right_y: Vec<Point> = points_y
        .iter()
        .filter(|p| p.x > left_x.last().unwrap().x)
        .map(|p| p.clone())
        .collect();
    let (l1, l2) = find_closest_pair_rec(left_x, left_y);
    let (r1, r2) = find_closest_pair_rec(right_x, right_y);

    let (delta, closest_pair) = if squared_dist(&l1, &l2) < squared_dist(&r1, &r2) {
        (squared_dist(&l1, &l2), (l1, l2))
    } else {
        (squared_dist(&r1, &r2), (r1, r2))
    };
    let s = find_split_pairs(points_x, points_y, delta);
    if s.is_some() {
        let (s1, s2) = s.unwrap();
        if squared_dist(&s1, &s2) < delta {
            return (s1, s2);
        }
    }
    closest_pair
}

fn find_split_pairs(
    points_x: Vec<Point>,
    points_y: Vec<Point>,
    delta: i32,
) -> Option<(Point, Point)> {
    let x_median = points_x[points_x.len() / 2].x;
    let mut splits = Vec::<Point>::with_capacity(points_y.len());
    for p in points_y {
        if p.x > x_median - delta && p.x < x_median + delta {
            splits.push(p);
        }
    }
    let mut closest = delta;
    let mut pair: Option<(Point, Point)> = None;
    for i in 0..splits.len() {
        let range = (i + 7).min(splits.len());
        for j in i + 1..range {
            let dist = squared_dist(&splits[i], &splits[j]);
            if dist < closest {
                closest = dist;
                pair = Some((splits[i].clone(), splits[j].clone()));
            }
        }
    }
    pair
}

fn exhaustive_search(points: &Vec<Point>) -> (Point, Point) {
    let n = points.len();
    let mut closest = squared_dist(&points[0], &points[1]);
    let mut pair = (&points[0], &points[1]);
    for i in 0..n {
        for j in i + 1..n {
            let dist = squared_dist(&points[i], &points[j]);
            if dist < closest {
                closest = dist;
                pair = (&points[i], &points[j]);
            }
        }
    }
    (pair.0.clone(), pair.1.clone())
}

fn squared_dist(p1: &Point, p2: &Point) -> i32 {
    (p1.x - p2.x).pow(2) + (p1.y - p2.y).pow(2)
}
