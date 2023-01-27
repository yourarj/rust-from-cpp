use std::time::Instant;

use ruster;

fn main() {
    let inst = Instant::now();
    ruster::raise_to_power(2, 25);
    let duration = inst.elapsed();
    println!("Time taken is {} nanos", duration.as_nanos());
}
