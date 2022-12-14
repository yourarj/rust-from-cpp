use std::pin::Pin;

#[repr(C)]
struct Package<'arr_life> {
    usixtyfour: u64, // 8 byte
    ssixtyfour: i64, // 8 byte
    uthirtytwo: u32, // 4 byte
    sthirtytwo: i32, // 4 byte
    usixteen: u16,   // 2 byte
    ssixteen: i16,   // 2 byte
    ueight: u8,      // 1 byte
    seight: i8,      // 1 byte
    arr_ptr: &'arr_life mut [[i8; 2]; 2],
}

impl<'arr_life> Package<'arr_life> {
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
        // for simplicity let mutate single element of slice
        self.arr_ptr[0][0] += 10;
    }
}

#[cxx::bridge]
mod ffi {

    #[namespace = "perf"]
    unsafe extern "C++" {
        include!("header.h");
        type Package;
        fn new_package() -> UniquePtr<Package>;
        fn get_a_mutable_pointer(self: Pin<&mut Package>) -> *mut i8;
    }

    #[namespace = "ruster_space"]
    extern "Rust" {
        unsafe fn mutate(pack: *mut Package);
        pub fn demonstrate_pinned() -> *mut i8;
    }
}

pub unsafe fn mutate(pack: *mut ffi::Package) {
    let rust_pack = pack as *mut Package;
    (*rust_pack).mutate_package();
}

pub fn demonstrate_pinned() -> *mut i8 {
    let mut pack = unsafe { Pin::from(Box::from_raw(ffi::new_package().into_raw())) };
    pack.as_mut().get_a_mutable_pointer()
}

#[cfg(test)]
mod tests {
    // use super::*;

    #[test]
    fn it_works() {}
}
