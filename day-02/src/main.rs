use std::fs;

#[derive(Debug, PartialEq, Clone, Copy)]
enum Direction {
    Increasing,
    Decreasing,
    NoChange,
}

fn main() {
    // let file_path = "./input.txt";
    let file_path = "./input2.txt";

    let reports: Vec<String> = fs::read_to_string(file_path)
        .unwrap()
        .lines()
        .map(String::from)
        .collect();

    let mut safe_reports = 0;
    for report in reports {
        println!("Report: {}", report);
        let levels: Vec<i32> = report
            .split_whitespace()
            .map(|x| x.parse::<i32>().unwrap())
            .collect();

        let chunks = levels.windows(2);

        let mut is_safe = false;
        let mut previous_direction: Option<Direction> = None;

        for item in chunks {
            let left = item[0];
            let right = item[1];

            let current_direction: Direction = if left > right {
                Direction::Decreasing
            } else if left < right {
                Direction::Increasing
            } else {
                Direction::NoChange
            };

            print!(
                "{:?} P: {:?} - C: {:?}",
                item, previous_direction, current_direction
            );

            is_safe = match previous_direction {
                Some(prev) => {
                    let diff = (left - right).abs();
                    print!(" - DIFF {}", diff);

                    prev == current_direction && diff != 0 && diff > 0 && diff <= 3
                }
                None => true,
            };

            println!("");

            if !is_safe {
                continue;
            }

            previous_direction = Some(current_direction);
        }

        if is_safe {
            safe_reports += 1;
        }

        println!("IS SAFE: {}\n", is_safe);
    }

    println!("Total safe reports: {}", safe_reports);
}
