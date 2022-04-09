use lupine::Lupine;

async fn main() {
    let engine = Lupine::new("Test", 600, 600);

    engine.await.run();
}
