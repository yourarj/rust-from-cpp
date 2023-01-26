pub fn raise_to_power(mut num: u64, mut pow: u64) -> u64 {
    while pow > 1 {
        num *= num;
        pow -= 1;
    }
    num
}

#[cxx::bridge]
mod ffi {

    #[namespace = "ruster_space"]
    extern "Rust" {
        pub fn raise_to_power(mut num: u64, pow: u64) -> u64;
    }
}

#[cfg(test)]
mod tests {
    // use super::*;

    #[test]
    fn it_works() {}
}
