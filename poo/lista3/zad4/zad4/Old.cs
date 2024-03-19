namespace Old {
	public class Rectangle
	{
		public virtual int Width { get; set; }
		public virtual int Height { get; set; }
	}

	public class Square : Rectangle
	{
		public override int Width
		{
			get { return base.Width; }
			set { base.Width = base.Height = value;}
		}

		public override int Height
		{
			get { return base.Height; }
			set { base.Width = base.Height = value; }
		}
	}

	//______________________kod kliencki_______________________________

	public class AreaCalculator
	{
		public int CalculateArea( Rectangle rect )
		{
			return rect.Width * rect.Height;
		}
	}
}