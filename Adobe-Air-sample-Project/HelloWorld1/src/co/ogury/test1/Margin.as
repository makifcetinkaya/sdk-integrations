package co.ogury.test1
{
	public class Margin
	{
		public var top:int;
		public var bottom:int;
		public var left:int;
		public var right:int;
		
		public function Margin( top:int = 0, bottom:int = 0, left:int = 0, right:int = 0 )
		{
			this.top    = top;
			this.bottom = bottom;
			this.left   = left;
			this.right  = right;
		}
		
		public function isEmpty():Boolean
		{
			if( ( top == 0 ) &&
				( bottom == 0 ) &&
				( left == 0 ) &&
				( right == 0 ) )
			{
				return true;
			}
			
			return false;
		}
	}
}