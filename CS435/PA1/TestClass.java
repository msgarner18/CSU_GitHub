public class TestClass {
	private static int CurrentVolume = 1;

	public void map() {
		System.out.println(TestClass.CurrentVolume++);
	}
}
