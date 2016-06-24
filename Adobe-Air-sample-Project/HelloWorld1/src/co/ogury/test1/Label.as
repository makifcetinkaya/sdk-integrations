package co.ogury.test1
{
	import flash.text.AntiAliasType;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFieldType;
	import flash.text.TextFormat;

	public class Label extends TextField
	{
		public function Label( txt:String, fontName:String, size:uint, color:uint )
		{
			super();
			_ctor( txt, fontName, size, color );
		}
		
		private function _ctor( txt:String, fontName:String, size:uint, color:uint ):void
		{
			mouseEnabled = false;
			type = TextFieldType.DYNAMIC;
			selectable = false;
			embedFonts = true;
			multiline = true;
			antiAliasType = AntiAliasType.ADVANCED;
			autoSize = TextFieldAutoSize.LEFT;
			defaultTextFormat = new TextFormat( fontName, size, color );
			text = txt;
		}
		
	}
}