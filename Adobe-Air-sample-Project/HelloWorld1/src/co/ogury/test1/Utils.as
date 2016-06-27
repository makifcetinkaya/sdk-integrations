package co.ogury.test1
{
	import flash.display.DisplayObject;
	import flash.display.Sprite;
	import flash.display.Stage;
	import flash.geom.ColorTransform;
	import flash.system.Capabilities;

	public class Utils
	{
		public function Utils()
		{
		}
		
		public static var dpi:uint = Capabilities.screenDPI;
		
		public static function colorize( target:DisplayObject, color:uint ):void
		{
			var ct:ColorTransform = new ColorTransform();
			ct.color = color;
			
			target.transform.colorTransform = ct;
		}
		
		public static function rectSprite( name:String, color:uint, width:uint, height:uint ):Sprite
		{
			var spr:Sprite = new Sprite();
				spr.name = name;
				spr.graphics.clear();
				spr.graphics.beginFill( color, 1.0 );
				spr.graphics.drawRect( 0, 0, width, height );
				spr.graphics.endFill();
			
			return spr;
		}
		
		public static function circleSprite( name:String, color:uint, radius:uint ):Sprite
		{
			var spr:Sprite = new Sprite();
				spr.name = name;
				spr.graphics.clear();
				spr.graphics.beginFill( color, 1.0 );
				spr.graphics.drawCircle( radius, radius, radius );
				spr.graphics.endFill();
			
			return spr;
		}
		
		public static function inchesToPixels(inches:Number):uint
		{
			return Math.round(dpi * inches);
		}
		
		public static function mmToPixels(mm:Number):uint
		{
			return Math.round(dpi * (mm / 25.4));
		}
		
		public static function place( parent:*, target:*,
							   alignement:Align = null, margin:Margin = null, centered:Boolean = false ):void
		{
			if( alignement == null ) { alignement = Align.none; }
			if( alignement == Align.none ) { return; }
			if( target == null ) { return; }
			
			if( !margin ) { margin = new Margin(); }
			
			var pX:Number;
			var pY:Number;
			var pW:Number;
			var pH:Number;
			
			var tX:Number;
			var tY:Number;
			var tW:Number;
			var tH:Number;
			
			var mW:Number;
			var mH:Number;
			
			var x:Number;
			var y:Number;
			
			
			if( ("x" in parent) && ("y" in parent) &&
				("width" in parent) && ("height" in parent) )
			{
				pX = parent.x;
				pY = parent.y;
				pW = parent.width;
				pH = parent.height;
			}
			else
			{
				throw new Error( "Could not find x/y/width/height in parent" );
			}
			
			if( parent is Stage )
			{
				pX = 0;
				pY = 0;
				pW = parent.stage.stageWidth;
				pH = parent.stage.stageHeight;
			}
			
			
			if( ("x" in target) && ("y" in target) &&
				("width" in target) && ("height" in target) )
			{
				tX = target.x;
				tY = target.y;
				tW = target.width;
				tH = target.height;
			}
			else
			{
				throw new Error( "Could not find x/y/width/height in target" );
			}
			
			mW = tW/2;
			mH = tH/2;
			
			//trace( "parent: x="+pX+", y="+pY+", w="+pW+", h="+pH );
			//trace( "target: x="+tX+", y="+tY+", w="+tW+", h="+tH );
			
			switch( alignement )
			{
				case Align.top:
					x = (pW/2)-(tW/2);
					y = pY + margin.top;
					if( centered ) { x += mW/2; y += mH; }
					break;
				
				case Align.bottom:
					x = (pW/2)-(tW/2);
					y = (pY+pH)-tH - margin.bottom;
					if( centered ) { x += mW/2; y += 0; }
					break;
				
				case Align.left:
					x = pX + margin.left;
					y = (pH/2)-(tH/2);
					if( centered ) { x += mW; y += mH/2; }
					break;
				
				case Align.right:
					x = (pX+pW)-tW - margin.right;
					y = (pH/2)-(tH/2);
					if( centered ) { x += 0; y += mH/2; }
					break;
				
				case Align.center:
					x = (pW/2)-(tW/2) + margin.left - margin.right;
					y = (pH/2)-(tH/2) + margin.top - margin.bottom;
					if( centered ) { x += mW/2; y += mH/2; }
					break;
				
				case Align.topLeft:
					x = pX + margin.left;
					y = pY + margin.top;
					if( centered ) { x += mW; y += mH; }
					break;
				
				case Align.topRight:
					x = (pX+pW)-tW - margin.right;
					y = pY + margin.top;
					if( centered ) { x += 0; y += mH; }
					break;
				
				case Align.bottomLeft:
					x = pX + margin.left;
					y = (pY+pH)-tH - margin.bottom;
					if( centered ) { x += mW; y += 0; }
					break;
				
				case Align.bottomRight:
					x = (pX+pW)-tW - margin.right;
					y = (pY+pH)-tH - margin.bottom;
					if( centered ) { x += 0; y += 0; }
					break;
			}
			
			//trace( "new X="+x+", Y="+y );
			
			target.x = x;
			target.y = y;
		}
		
	}
}