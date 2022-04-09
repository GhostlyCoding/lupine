use winit::{
    event::*,
    event_loop::{ControlFlow, EventLoop},
    window::WindowBuilder,
    window::Window,
};

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}

pub enum LupineEvents {
    RESIZE(winit::dpi::PhysicalSize<u32>)
}

impl Copy for LupineEvents {}

impl Clone for LupineEvents {
    fn clone(&self) -> Self {
        *self
    }
}

pub struct Lupine {
    runner: Runner,
    events: Vec<LupineEvents>,
    surface: wgpu::Surface,
    device: wgpu::Device,
    queue: wgpu::Queue,
    config: wgpu::SurfaceConfiguration,
    size: winit::dpi::PhysicalSize<u32>,
}

impl Lupine {
    pub async fn new(title: &str, width: u32, height: u32) -> Self {
        env_logger::init();
        let event_loop = EventLoop::new();
        let window = WindowBuilder::new().with_inner_size(winit::dpi::LogicalSize { width, height })
            .with_title(title).build(&event_loop).unwrap();


        let runner = Runner::new(window, event_loop);

        let size = runner.window.inner_size();
        let instance = wgpu::Instance::new(wgpu::Backends::all());
        let surface = unsafe { instance.create_surface(&runner.window) };
        let adapter = instance.request_adapter(
            &wgpu::RequestAdapterOptions {
                power_preference: wgpu::PowerPreference::default(),
                compatible_surface: Some(&surface),
                force_fallback_adapter: false,
            }
        ).await.unwrap();

        let (device, queue) = adapter.request_device(
            &wgpu::DeviceDescriptor {
                features: wgpu::Features::empty(),
                limits: if cfg!(target_arch = "wasm32") {
                    wgpu::Limits::downlevel_webgl2_defaults()
                } else {
                    wgpu::Limits::default()
                },
                label: None,
            },
            None,
        ).await.unwrap();

        let config = wgpu::SurfaceConfiguration {
            usage: wgpu::TextureUsages::RENDER_ATTACHMENT,
            format: surface.get_preferred_format(&adapter).unwrap(),
            width: size.width,
            height: size.height,
            present_mode: wgpu::PresentMode::Fifo,
        };
        surface.configure(&device, &config);

        Self {
            runner,
            events: Vec::new(),
            surface,
            device,
            queue,
            config,
            size
        }
    }
    
    pub fn resize_window(&mut self, new_size: winit::dpi::PhysicalSize<u32>) {
        if new_size.width > 0 && new_size.height > 0 {
            self.size = new_size;
            self.config.width = new_size.width;
            self.config.height = new_size.height;
            self.surface.configure(&self.device, &self.config);
        }
    }

    pub fn run(&mut self) {
    }
    pub fn poll_events(&mut self) -> Vec<LupineEvents> {
        let return_event = self.events.clone();
        self.events.clear();
        return_event
    }

}

pub struct Runner {
    window: winit::window::Window,
    event_loop: winit::event_loop::EventLoop<()>,
    events: Vec<LupineEvents>,
}

impl Runner {
    pub fn new(window: winit::window::Window, event_loop: EventLoop<()>) -> Self {
        Self {
            window,
            event_loop,
            events: Vec::new()
        }
    }
    pub fn run(&'static &mut self) {
        self.event_loop.run(move |event, _, control_flow| {
            match event { 
                Event::WindowEvent {
                    ref event,
                    window_id,
                } if window_id == self.window.id() => if !self.input(event) {
                    match event {
                        WindowEvent::CloseRequested => *control_flow = ControlFlow::Exit,
                        WindowEvent::Resized(physical_size) => {
                            self.events.push(LupineEvents::RESIZE(*physical_size));
                        },
                        WindowEvent::ScaleFactorChanged { new_inner_size, .. } => {
                            self.events.push(LupineEvents::RESIZE(**new_inner_size));
                        },
                        _ => {}
                    }
                },
                _ => {}
            }

        });
        panic!("How did we get here?");
    }
    fn input(&mut self, event: &WindowEvent) -> bool {
        false
    }
}
