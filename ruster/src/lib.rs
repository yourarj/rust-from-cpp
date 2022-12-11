#[repr(C)]
struct Package {
    usixtyfour: u64, // 8 byte
    ssixtyfour: i64, // 8 byte
    uthirtytwo: u32, // 4 byte
    sthirtytwo: i32, // 4 byte
    usixteen: u16,   // 2 byte
    ssixteen: i16,   // 2 byte
    ueight: u8,      // 1 byte
    seight: i8,      // 1 byte
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
