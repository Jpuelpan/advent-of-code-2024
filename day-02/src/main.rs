use std::fs;

#[derive(Debug, PartialEq, Clone, Copy)]
enum Direction {
    Increasing,
    Decreasing,
    NoChange,
}

fn is_report_safe(levels: Vec<i32>) -> bool {
    let mut is_safe = false;

    let chunks = levels.windows(2);
    let mut previous_direction: Option<Direction> = None;

    for item in chunks {
        let left = item[0];
        let right = item[1];
        let diff = (left - right).abs();

        let current_direction: Direction = if left > right {
            Direction::Decreasing
        } else if left < right {
            Direction::Increasing
        } else {
            Direction::NoChange
        };

        // print!(
        //     "{:?} PRE: {:?} - CUR: {:?} - DIFF: {:?}",
        //     item, previous_direction, current_direction, diff
        // );

        is_safe = match previous_direction {
            Some(prev) => prev == current_direction && diff != 0 && diff > 0 && diff <= 3,
            None => diff != 0 && diff > 0 && diff <= 3,
        };

        // println!("");
        if !is_safe {
            break;
        }

        previous_direction = Some(current_direction);
    }

    return is_safe;
}

fn report_dampener(levels: Vec<i32>) -> bool {
    // println!("Dampening report {:?} ({})", levels, levels.len());

    let mut is_safe = false;
    for i in 0..levels.len() {
        let levels_filtered = levels
            .iter()
            .enumerate()
            .filter(|&(x, _)| i != x)
            .map(|(_, x)| *x);

        let items: Vec<i32> = levels_filtered.collect();
        is_safe = is_report_safe(items.clone());
        // println!("items: {:?}, idx: {}, safe: {}", items, i, is_safe);

        if is_safe {
            break;
        }
    }

    return is_safe;
}

fn main() {
    let file_path = "./input.txt";

    let reports: Vec<String> = fs::read_to_string(file_path)
        .unwrap()
        .lines()
        .map(String::from)
        .collect();

    let mut safe_reports = 0;
    for report in reports {
        let levels: Vec<i32> = report
            .split_whitespace()
            .map(|x| x.parse::<i32>().unwrap())
            .collect();

        let mut is_safe = is_report_safe(levels.clone());

        if !is_safe {
            is_safe = report_dampener(levels.clone());
        }

        if is_safe {
            safe_reports += 1;
        }

        println!("{:?} - {}", levels, is_safe);
    }

    println!("Total safe reports: {}", safe_reports);
}
