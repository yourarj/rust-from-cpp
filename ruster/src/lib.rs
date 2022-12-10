#[repr(C)]
struct Package {
    usixtyfour: u64,
    ssixtyfour: i64,
    uthirtytwo: u32,
    sthirtytwo: i32,
    usixteen: u16,
    ssixteen: i16,
    ueight: u8,
    seight: i8,
}

impl Package {
    #[inline]
    pub fn mutate_package(&mut self) {
        self.ueight *= 2;
        self.usixteen *= 2;
        self.uthirtytwo *= 2;
        self.usixtyfour *= 2;
        self.seight *= 2;
        self.ssixteen *= 2;
        self.sthirtytwo *= 2;
        self.ssixtyfour *= 2;
    }
}

#[cxx::bridge]
mod ffi {

    #[namespace = "perf"]
    unsafe extern "C++" {
        include!("header.h");
        type Package;
    }

    #[namespace = "ruster_space"]
    extern "Rust" {
        unsafe fn mutate(pack: *mut Package);
    }
}

pub unsafe fn mutate(pack: *mut ffi::Package) {
    let rust_pack = pack as *mut Package;
    (*rust_pack).mutate_package();
}

#[cfg(test)]
mod tests {
    // use super::*;

    #[test]
    fn it_works() {}
}
