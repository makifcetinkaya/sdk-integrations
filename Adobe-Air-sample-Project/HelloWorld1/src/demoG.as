package
{
    import flash.desktop.NativeApplication;
    import flash.display.Bitmap;
    import flash.display.Sprite;
    import flash.display.StageAlign;
    import flash.display.StageQuality;
    import flash.display.StageScaleMode;
    import flash.events.Event;
    import flash.events.MouseEvent;
    import flash.events.UncaughtErrorEvent;
    import flash.text.Font;
    import flash.text.TextField;
    
    import co.ogury.test1.Align;
    import co.ogury.test1.Label;
    import co.ogury.test1.Logo;
    import co.ogury.test1.Margin;
    import co.ogury.test1.Palette;
    import co.ogury.test1.Utils;
    import co.ogury.test1.fonts.OpenSans;
    
    import io.presage.extensions.Presage;
    import io.presage.extensions.events.PresageEvent;
    
    //[SWF(width="600", height="800", frameRate="24", backgroundColor="#ffffff")]
    public class demoG extends Sprite
    {
        public var base:Sprite;
        public var background:Sprite;
        public var title:TextField;
        public var received:TextField;
        public var logo:Sprite;
        
        public var area:Sprite;
        public var startButton:Sprite;
        public var startLabel:TextField;
        public var showButton:Sprite;
        public var showLabel:TextField;
        
        public function demoG()
        {
            super();
            
            _ctor();
        }
        
        private function _ctor():void
        {
            if( stage )
            {
                onAddedToStage();
            }
            else
            {
                addEventListener( Event.ADDED_TO_STAGE, onAddedToStage );
            }
        }
        
        public function onGlobalError( event:UncaughtErrorEvent = null ):void
        {
            event.preventDefault();
            event.stopImmediatePropagation();
            
            var message:String = "";
            
            if( event && event.error )
            {
                
                if( event.error.message )
                {
                    message = event.error.message;
                }
                else if( event.error.text )
                {
                    message = event.error.text;
                }
                else
                {
                    message = event.error.toString();
                }
                
            }
            else
            {
                message = "unknown";
            }
            
            trace( "Uncaught Error: " + message );
        }
        
        private function onAddedToStage( event:Event = null ):void
        {
            removeEventListener( Event.ADDED_TO_STAGE, onAddedToStage );
            loaderInfo.uncaughtErrorEvents.addEventListener( UncaughtErrorEvent.UNCAUGHT_ERROR, onGlobalError );
            main();
        }
        
        private var _aligned:Boolean = false
        
        private function onActivate( event:Event ):void
        {
            trace( "onActivate()" );
        }
        
        private function onDeactivate( event:Event ):void
        {
            trace( "onDeactivate()" );
        }
        
        private function onResize( event:Event = null ):void
        {
            trace( "onResize()" );
            
            if( !stage.autoOrients && !_aligned )
            {
                var W:uint = stage.fullScreenWidth;
                var H:uint = stage.fullScreenHeight;
                
                trace( stage.orientation );
                trace( "w="+W+", h="+H );
                
                background.width  = W;
                background.height = H;
                
                Utils.place( base, logo, Align.bottom, new Margin( 0, Utils.mmToPixels(5) ) );
                Utils.place( base, area, Align.center, new Margin( Utils.mmToPixels(20) ) );
                Utils.place( area, startButton, Align.bottomLeft );
                Utils.place( area, showButton, Align.bottomRight );
                
                received.y = title.height + 20;
                
                _aligned = true;
            }
            
        }
        
        private function onClick( event:MouseEvent ):void
        {
            trace( "onClick()" );
            received.text = "DEBUG";
                                                                                                                                                                                                                                                        
            var id:String = presage.id;
            trace( "presage.id = " + id );
            
            var env:String = presage.env;
            trace( "presage.env = " + env );
            
            var key:String = presage.key;
            trace( "presage.key = " + key );
            
            var ready:Boolean = presage.isSDKReady()
            trace( "presage.isSDKReady = " + ready );
        }
        
        private var _started:Boolean = false;
        
        private function onClickStart( event:MouseEvent ):void
        {
            trace( "onClickStart()" );
            
            if( !_started )
            {
                trace( "presage.startPresage()" );
                received.text = "startPresage()";
                
                presage.start();
                _started = true;
            }
            else
            {
                trace( "presage.restart()" );
                received.text = "restart()";
                
                presage.restart();
            }

            // alternative
            // Presage.StartPresage();
        }
        
        private function onClickShow( event:MouseEvent ):void
        {
            trace( "onClickShow()" );
            received.text = "showInterstitial()";

            presage.showLoadedAds();

            // alternative
            // Presage.ShowInterstitial();
        }
        
        private function onAdEvent( event:PresageEvent ):void
        {
            switch( event.type )
            {
                case PresageEvent.AD_NOT_FOUND:
                trace( "onAdEvent() - AD_NOT_FOUND" );
                received.text = "AD_NOT_FOUND";
                break;
                
                case PresageEvent.AD_FOUND:
                trace( "onAdEvent() - AD_FOUND" );
                received.text = "AD_FOUND";
                break;
                
                case PresageEvent.AD_CLOSED:
                trace( "onAdEvent() - AD_CLOSED" );
                received.text = "AD_CLOSED";
                break;

                case PresageEvent.AD_ERROR:
                trace( "onAdEvent() - AD_ERROR" );
                received.text = "AD_ERROR";
                break;

                case PresageEvent.AD_DISPLAYED:
                trace( "onAdEvent() - AD_DISPLAYED" );
                received.text = "AD_DISPLAYED";
                break;

                case PresageEvent.EULA_FOUND:
                    trace( "onAdEvent() - EULA_FOUND" );
                    received.text = "EULA_FOUND";
                    break;

                case PresageEvent.EULA_NOT_FOUND:
                    trace( "onAdEvent() - EULA_NOT_FOUND" );
                    received.text = "EULA_NOT_FOUND";
                    break;

                case PresageEvent.EULA_CLOSED:
                    trace( "onAdEvent() - EULA_CLOSED" );
                    received.text = "EULA_CLOSED";
                    break;
            }
        }
        
        public var presage:Presage;
        
        private var _initialized:Boolean = false;
        
        public function main():void
        {
            if( _initialized )
            {
                return;
            }
            
            trace( "hello world" );
            
            //config
            stage.align     = StageAlign.TOP_LEFT;
            stage.scaleMode = StageScaleMode.NO_SCALE;
            stage.quality   = StageQuality.BEST;
            
            stage.autoOrients = false;
            
            //NativeApplication.nativeApplication.executeInBackground = true;
            
            //font
            Font.registerFont( OpenSans.bold );
            Font.registerFont( OpenSans.boldItalic );
            Font.registerFont( OpenSans.extraBold );
            Font.registerFont( OpenSans.extraBoldItalic );
            Font.registerFont( OpenSans.italic );
            Font.registerFont( OpenSans.light );
            Font.registerFont( OpenSans.lightItalic );
            Font.registerFont( OpenSans.regular );
            Font.registerFont( OpenSans.semiBold );
            Font.registerFont( OpenSans.semiBoldItalic );
            
            //components
            trace( "Presage v" + Presage.version );
            trace( "Presage supported: " + Presage.isSupported() );

            Presage.enableDebugTrace    = true;
            Presage.enableErrorChecking = true;

            //presage = new Presage();
            presage = Presage.getInstance();
            
            
            //UI
            //Utils.dpi = 160;
            trace( "      screen DPI = " + Utils.dpi );
            trace( "      stageWidth = " + stage.stageWidth );
            trace( "     stageHeight = " + stage.stageHeight );
            trace( " fullScreenWidth = " + stage.fullScreenWidth );
            trace( "fullScreenHeight = " + stage.fullScreenHeight );
            
            
            base = new Sprite();
            background = Utils.rectSprite( "background", Palette.ogury, stage.fullScreenWidth, stage.fullScreenHeight );
            title = new Label( "Ogury Presage" , "OpenSans-ExtraBold", Utils.mmToPixels(4), Palette.white );
            title.name = "title";
            
            received = new Label( "(empty)" , "OpenSans-ExtraBold", Utils.mmToPixels(2), Palette.cutter );
            received.name = "received";
            
            var gfx:Bitmap = new Logo();
            logo = Utils.circleSprite( "logo", Palette.white, Utils.mmToPixels(6) );
            logo.addChild( gfx );
                gfx.width = logo.width * 0.9;
                gfx.height = logo.height * 0.9;
                Utils.place( logo, gfx, Align.center );
            
            area =  Utils.rectSprite( "area", Palette.white, Utils.mmToPixels(32), Utils.mmToPixels(16) );
            area.alpha = 0;
            
            startButton = Utils.circleSprite( "startButton", Palette.green, Utils.mmToPixels(6) );
            startLabel  = new Label( "start" , "OpenSans-ExtraBold", Utils.mmToPixels(4), Palette.white );
            
            showButton = Utils.circleSprite( "showButton", Palette.cutter, Utils.mmToPixels(6) );
            showLabel  = new Label( "show" , "OpenSans-ExtraBold", Utils.mmToPixels(4), Palette.black );
            
            //events
            stage.addEventListener( Event.RESIZE, onResize );
            logo.addEventListener( MouseEvent.CLICK, onClick );
            startButton.addEventListener( MouseEvent.CLICK, onClickStart );
            showButton.addEventListener( MouseEvent.CLICK, onClickShow );
            NativeApplication.nativeApplication.addEventListener( Event.ACTIVATE, onActivate );
            NativeApplication.nativeApplication.addEventListener( Event.DEACTIVATE, onDeactivate );
            
            presage.addEventListener( PresageEvent.AD_NOT_FOUND, onAdEvent );
            presage.addEventListener( PresageEvent.AD_FOUND, onAdEvent );
            presage.addEventListener( PresageEvent.AD_CLOSED, onAdEvent );
            presage.addEventListener( PresageEvent.AD_ERROR, onAdEvent );
            presage.addEventListener( PresageEvent.AD_DISPLAYED, onAdEvent );

            presage.addEventListener( PresageEvent.EULA_FOUND, onAdEvent );
            presage.addEventListener( PresageEvent.EULA_NOT_FOUND, onAdEvent );
            presage.addEventListener( PresageEvent.EULA_CLOSED, onAdEvent );
            
            addChild( base );
                base.addChild( background );
                base.addChild( title );
                base.addChild( received );
                received.y = title.height + 20;
                base.addChild( logo );
                base.addChild( area );
                base.addChild( startButton );
                startButton.addChild( startLabel );
                startLabel.x += 10;
                startLabel.y += 30;
                base.addChild( showButton );
                showButton.addChild( showLabel );
                showLabel.x += 10;
                showLabel.y += 30;
            
            onResize();
            _initialized = true;
        }
        
    }
    
}