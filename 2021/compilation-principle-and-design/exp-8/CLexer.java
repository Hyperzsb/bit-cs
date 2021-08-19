// Generated from C.g4 by ANTLR 4.9
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class CLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		Break=1, Case=2, Char=3, Continue=4, Default=5, Do=6, Double=7, Else=8, 
		Float=9, For=10, Goto=11, If=12, Int=13, Return=14, Sizeof=15, Void=16, 
		While=17, LeftParen=18, RightParen=19, LeftBracket=20, RightBracket=21, 
		LeftBrace=22, RightBrace=23, Less=24, LessEqual=25, Greater=26, GreaterEqual=27, 
		Plus=28, PlusPlus=29, Minus=30, MinusMinus=31, Star=32, Div=33, Mod=34, 
		And=35, Or=36, AndAnd=37, OrOr=38, Caret=39, Not=40, Tilde=41, Question=42, 
		Colon=43, Semi=44, Comma=45, Assign=46, StarAssign=47, DivAssign=48, ModAssign=49, 
		PlusAssign=50, MinusAssign=51, AndAssign=52, XorAssign=53, OrAssign=54, 
		Equal=55, NotEqual=56, Identifier=57, IntegerConstant=58, FloatingConstant=59, 
		DigitSequence=60, CharacterConstant=61, StringLiteral=62, Whitespace=63, 
		Newline=64, BlockComment=65, LineComment=66;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"Break", "Case", "Char", "Continue", "Default", "Do", "Double", "Else", 
			"Float", "For", "Goto", "If", "Int", "Return", "Sizeof", "Void", "While", 
			"LeftParen", "RightParen", "LeftBracket", "RightBracket", "LeftBrace", 
			"RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", "Plus", 
			"PlusPlus", "Minus", "MinusMinus", "Star", "Div", "Mod", "And", "Or", 
			"AndAnd", "OrOr", "Caret", "Not", "Tilde", "Question", "Colon", "Semi", 
			"Comma", "Assign", "StarAssign", "DivAssign", "ModAssign", "PlusAssign", 
			"MinusAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", "NotEqual", 
			"Identifier", "IdentifierNondigit", "Nondigit", "Digit", "UniversalCharacterName", 
			"HexQuad", "IntegerConstant", "BinaryConstant", "DecimalConstant", "OctalConstant", 
			"HexadecimalConstant", "HexadecimalPrefix", "NonzeroDigit", "OctalDigit", 
			"HexadecimalDigit", "IntegerSuffix", "UnsignedSuffix", "LongSuffix", 
			"LongLongSuffix", "FloatingConstant", "DecimalFloatingConstant", "HexadecimalFloatingConstant", 
			"FractionalConstant", "ExponentPart", "Sign", "DigitSequence", "HexadecimalFractionalConstant", 
			"BinaryExponentPart", "HexadecimalDigitSequence", "FloatingSuffix", "CharacterConstant", 
			"CCharSequence", "CChar", "EscapeSequence", "SimpleEscapeSequence", "OctalEscapeSequence", 
			"HexadecimalEscapeSequence", "StringLiteral", "EncodingPrefix", "SCharSequence", 
			"SChar", "Whitespace", "Newline", "BlockComment", "LineComment"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'break'", "'case'", "'char'", "'continue'", "'default'", "'do'", 
			"'double'", "'else'", "'float'", "'for'", "'goto'", "'if'", "'int'", 
			"'return'", "'sizeof'", "'void'", "'while'", "'('", "')'", "'['", "']'", 
			"'{'", "'}'", "'<'", "'<='", "'>'", "'>='", "'+'", "'++'", "'-'", "'--'", 
			"'*'", "'/'", "'%'", "'&'", "'|'", "'&&'", "'||'", "'^'", "'!'", "'~'", 
			"'?'", "':'", "';'", "','", "'='", "'*='", "'/='", "'%='", "'+='", "'-='", 
			"'&='", "'^='", "'|='", "'=='", "'!='"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "Break", "Case", "Char", "Continue", "Default", "Do", "Double", 
			"Else", "Float", "For", "Goto", "If", "Int", "Return", "Sizeof", "Void", 
			"While", "LeftParen", "RightParen", "LeftBracket", "RightBracket", "LeftBrace", 
			"RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", "Plus", 
			"PlusPlus", "Minus", "MinusMinus", "Star", "Div", "Mod", "And", "Or", 
			"AndAnd", "OrOr", "Caret", "Not", "Tilde", "Question", "Colon", "Semi", 
			"Comma", "Assign", "StarAssign", "DivAssign", "ModAssign", "PlusAssign", 
			"MinusAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", "NotEqual", 
			"Identifier", "IntegerConstant", "FloatingConstant", "DigitSequence", 
			"CharacterConstant", "StringLiteral", "Whitespace", "Newline", "BlockComment", 
			"LineComment"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public CLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "C.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2D\u02c1\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t="+
		"\4>\t>\4?\t?\4@\t@\4A\tA\4B\tB\4C\tC\4D\tD\4E\tE\4F\tF\4G\tG\4H\tH\4I"+
		"\tI\4J\tJ\4K\tK\4L\tL\4M\tM\4N\tN\4O\tO\4P\tP\4Q\tQ\4R\tR\4S\tS\4T\tT"+
		"\4U\tU\4V\tV\4W\tW\4X\tX\4Y\tY\4Z\tZ\4[\t[\4\\\t\\\4]\t]\4^\t^\4_\t_\4"+
		"`\t`\4a\ta\4b\tb\4c\tc\4d\td\4e\te\4f\tf\3\2\3\2\3\2\3\2\3\2\3\2\3\3\3"+
		"\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5"+
		"\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\b\3\b\3\b\3\b\3\b\3\b\3"+
		"\b\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\f"+
		"\3\f\3\f\3\f\3\f\3\r\3\r\3\r\3\16\3\16\3\16\3\16\3\17\3\17\3\17\3\17\3"+
		"\17\3\17\3\17\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\21\3\21\3\21\3\21\3"+
		"\21\3\22\3\22\3\22\3\22\3\22\3\22\3\23\3\23\3\24\3\24\3\25\3\25\3\26\3"+
		"\26\3\27\3\27\3\30\3\30\3\31\3\31\3\32\3\32\3\32\3\33\3\33\3\34\3\34\3"+
		"\34\3\35\3\35\3\36\3\36\3\36\3\37\3\37\3 \3 \3 \3!\3!\3\"\3\"\3#\3#\3"+
		"$\3$\3%\3%\3&\3&\3&\3\'\3\'\3\'\3(\3(\3)\3)\3*\3*\3+\3+\3,\3,\3-\3-\3"+
		".\3.\3/\3/\3\60\3\60\3\60\3\61\3\61\3\61\3\62\3\62\3\62\3\63\3\63\3\63"+
		"\3\64\3\64\3\64\3\65\3\65\3\65\3\66\3\66\3\66\3\67\3\67\3\67\38\38\38"+
		"\39\39\39\3:\3:\3:\7:\u018e\n:\f:\16:\u0191\13:\3;\3;\5;\u0195\n;\3<\3"+
		"<\3=\3=\3>\3>\3>\3>\3>\3>\3>\3>\3>\3>\5>\u01a5\n>\3?\3?\3?\3?\3?\3@\3"+
		"@\5@\u01ae\n@\3@\3@\5@\u01b2\n@\3@\3@\5@\u01b6\n@\3@\5@\u01b9\n@\3A\3"+
		"A\3A\6A\u01be\nA\rA\16A\u01bf\3B\3B\7B\u01c4\nB\fB\16B\u01c7\13B\3C\3"+
		"C\7C\u01cb\nC\fC\16C\u01ce\13C\3D\3D\6D\u01d2\nD\rD\16D\u01d3\3E\3E\3"+
		"E\3F\3F\3G\3G\3H\3H\3I\3I\5I\u01e1\nI\3I\3I\3I\3I\3I\5I\u01e8\nI\3I\3"+
		"I\5I\u01ec\nI\5I\u01ee\nI\3J\3J\3K\3K\3L\3L\3L\3L\5L\u01f8\nL\3M\3M\5"+
		"M\u01fc\nM\3N\3N\5N\u0200\nN\3N\5N\u0203\nN\3N\3N\3N\5N\u0208\nN\5N\u020a"+
		"\nN\3O\3O\3O\5O\u020f\nO\3O\3O\5O\u0213\nO\3P\5P\u0216\nP\3P\3P\3P\3P"+
		"\3P\5P\u021d\nP\3Q\3Q\5Q\u0221\nQ\3Q\3Q\3R\3R\3S\6S\u0228\nS\rS\16S\u0229"+
		"\3T\5T\u022d\nT\3T\3T\3T\3T\3T\5T\u0234\nT\3U\3U\5U\u0238\nU\3U\3U\3V"+
		"\6V\u023d\nV\rV\16V\u023e\3W\3W\3X\3X\3X\3X\3X\3X\3X\3X\3X\3X\3X\3X\3"+
		"X\3X\3X\3X\3X\3X\3X\3X\3X\3X\5X\u0259\nX\3Y\6Y\u025c\nY\rY\16Y\u025d\3"+
		"Z\3Z\5Z\u0262\nZ\3[\3[\3[\3[\5[\u0268\n[\3\\\3\\\3\\\3]\3]\3]\5]\u0270"+
		"\n]\3]\5]\u0273\n]\3^\3^\3^\3^\6^\u0279\n^\r^\16^\u027a\3_\5_\u027e\n"+
		"_\3_\3_\5_\u0282\n_\3_\3_\3`\3`\3`\5`\u0289\n`\3a\6a\u028c\na\ra\16a\u028d"+
		"\3b\3b\3b\3b\3b\3b\3b\5b\u0297\nb\3c\6c\u029a\nc\rc\16c\u029b\3c\3c\3"+
		"d\3d\5d\u02a2\nd\3d\5d\u02a5\nd\3d\3d\3e\3e\3e\3e\7e\u02ad\ne\fe\16e\u02b0"+
		"\13e\3e\3e\3e\3e\3e\3f\3f\3f\3f\7f\u02bb\nf\ff\16f\u02be\13f\3f\3f\3\u02ae"+
		"\2g\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35"+
		"\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\359\36"+
		";\37= ?!A\"C#E$G%I&K\'M(O)Q*S+U,W-Y.[/]\60_\61a\62c\63e\64g\65i\66k\67"+
		"m8o9q:s;u\2w\2y\2{\2}\2\177<\u0081\2\u0083\2\u0085\2\u0087\2\u0089\2\u008b"+
		"\2\u008d\2\u008f\2\u0091\2\u0093\2\u0095\2\u0097\2\u0099=\u009b\2\u009d"+
		"\2\u009f\2\u00a1\2\u00a3\2\u00a5>\u00a7\2\u00a9\2\u00ab\2\u00ad\2\u00af"+
		"?\u00b1\2\u00b3\2\u00b5\2\u00b7\2\u00b9\2\u00bb\2\u00bd@\u00bf\2\u00c1"+
		"\2\u00c3\2\u00c5A\u00c7B\u00c9C\u00cbD\3\2\26\5\2C\\aac|\3\2\62;\4\2D"+
		"Ddd\3\2\62\63\4\2ZZzz\3\2\63;\3\2\629\5\2\62;CHch\4\2WWww\4\2NNnn\4\2"+
		"GGgg\4\2--//\4\2RRrr\6\2HHNNhhnn\6\2\f\f\17\17))^^\f\2$$))AA^^cdhhppt"+
		"tvvxx\5\2NNWWww\6\2\f\f\17\17$$^^\4\2\13\13\"\"\4\2\f\f\17\17\2\u02d8"+
		"\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2"+
		"\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2"+
		"\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2"+
		"\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2"+
		"\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3"+
		"\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2"+
		"\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2S\3\2\2\2\2"+
		"U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\2a\3"+
		"\2\2\2\2c\3\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2\2\2\2k\3\2\2\2\2m\3\2\2"+
		"\2\2o\3\2\2\2\2q\3\2\2\2\2s\3\2\2\2\2\177\3\2\2\2\2\u0099\3\2\2\2\2\u00a5"+
		"\3\2\2\2\2\u00af\3\2\2\2\2\u00bd\3\2\2\2\2\u00c5\3\2\2\2\2\u00c7\3\2\2"+
		"\2\2\u00c9\3\2\2\2\2\u00cb\3\2\2\2\3\u00cd\3\2\2\2\5\u00d3\3\2\2\2\7\u00d8"+
		"\3\2\2\2\t\u00dd\3\2\2\2\13\u00e6\3\2\2\2\r\u00ee\3\2\2\2\17\u00f1\3\2"+
		"\2\2\21\u00f8\3\2\2\2\23\u00fd\3\2\2\2\25\u0103\3\2\2\2\27\u0107\3\2\2"+
		"\2\31\u010c\3\2\2\2\33\u010f\3\2\2\2\35\u0113\3\2\2\2\37\u011a\3\2\2\2"+
		"!\u0121\3\2\2\2#\u0126\3\2\2\2%\u012c\3\2\2\2\'\u012e\3\2\2\2)\u0130\3"+
		"\2\2\2+\u0132\3\2\2\2-\u0134\3\2\2\2/\u0136\3\2\2\2\61\u0138\3\2\2\2\63"+
		"\u013a\3\2\2\2\65\u013d\3\2\2\2\67\u013f\3\2\2\29\u0142\3\2\2\2;\u0144"+
		"\3\2\2\2=\u0147\3\2\2\2?\u0149\3\2\2\2A\u014c\3\2\2\2C\u014e\3\2\2\2E"+
		"\u0150\3\2\2\2G\u0152\3\2\2\2I\u0154\3\2\2\2K\u0156\3\2\2\2M\u0159\3\2"+
		"\2\2O\u015c\3\2\2\2Q\u015e\3\2\2\2S\u0160\3\2\2\2U\u0162\3\2\2\2W\u0164"+
		"\3\2\2\2Y\u0166\3\2\2\2[\u0168\3\2\2\2]\u016a\3\2\2\2_\u016c\3\2\2\2a"+
		"\u016f\3\2\2\2c\u0172\3\2\2\2e\u0175\3\2\2\2g\u0178\3\2\2\2i\u017b\3\2"+
		"\2\2k\u017e\3\2\2\2m\u0181\3\2\2\2o\u0184\3\2\2\2q\u0187\3\2\2\2s\u018a"+
		"\3\2\2\2u\u0194\3\2\2\2w\u0196\3\2\2\2y\u0198\3\2\2\2{\u01a4\3\2\2\2}"+
		"\u01a6\3\2\2\2\177\u01b8\3\2\2\2\u0081\u01ba\3\2\2\2\u0083\u01c1\3\2\2"+
		"\2\u0085\u01c8\3\2\2\2\u0087\u01cf\3\2\2\2\u0089\u01d5\3\2\2\2\u008b\u01d8"+
		"\3\2\2\2\u008d\u01da\3\2\2\2\u008f\u01dc\3\2\2\2\u0091\u01ed\3\2\2\2\u0093"+
		"\u01ef\3\2\2\2\u0095\u01f1\3\2\2\2\u0097\u01f7\3\2\2\2\u0099\u01fb\3\2"+
		"\2\2\u009b\u0209\3\2\2\2\u009d\u020b\3\2\2\2\u009f\u021c\3\2\2\2\u00a1"+
		"\u021e\3\2\2\2\u00a3\u0224\3\2\2\2\u00a5\u0227\3\2\2\2\u00a7\u0233\3\2"+
		"\2\2\u00a9\u0235\3\2\2\2\u00ab\u023c\3\2\2\2\u00ad\u0240\3\2\2\2\u00af"+
		"\u0258\3\2\2\2\u00b1\u025b\3\2\2\2\u00b3\u0261\3\2\2\2\u00b5\u0267\3\2"+
		"\2\2\u00b7\u0269\3\2\2\2\u00b9\u026c\3\2\2\2\u00bb\u0274\3\2\2\2\u00bd"+
		"\u027d\3\2\2\2\u00bf\u0288\3\2\2\2\u00c1\u028b\3\2\2\2\u00c3\u0296\3\2"+
		"\2\2\u00c5\u0299\3\2\2\2\u00c7\u02a4\3\2\2\2\u00c9\u02a8\3\2\2\2\u00cb"+
		"\u02b6\3\2\2\2\u00cd\u00ce\7d\2\2\u00ce\u00cf\7t\2\2\u00cf\u00d0\7g\2"+
		"\2\u00d0\u00d1\7c\2\2\u00d1\u00d2\7m\2\2\u00d2\4\3\2\2\2\u00d3\u00d4\7"+
		"e\2\2\u00d4\u00d5\7c\2\2\u00d5\u00d6\7u\2\2\u00d6\u00d7\7g\2\2\u00d7\6"+
		"\3\2\2\2\u00d8\u00d9\7e\2\2\u00d9\u00da\7j\2\2\u00da\u00db\7c\2\2\u00db"+
		"\u00dc\7t\2\2\u00dc\b\3\2\2\2\u00dd\u00de\7e\2\2\u00de\u00df\7q\2\2\u00df"+
		"\u00e0\7p\2\2\u00e0\u00e1\7v\2\2\u00e1\u00e2\7k\2\2\u00e2\u00e3\7p\2\2"+
		"\u00e3\u00e4\7w\2\2\u00e4\u00e5\7g\2\2\u00e5\n\3\2\2\2\u00e6\u00e7\7f"+
		"\2\2\u00e7\u00e8\7g\2\2\u00e8\u00e9\7h\2\2\u00e9\u00ea\7c\2\2\u00ea\u00eb"+
		"\7w\2\2\u00eb\u00ec\7n\2\2\u00ec\u00ed\7v\2\2\u00ed\f\3\2\2\2\u00ee\u00ef"+
		"\7f\2\2\u00ef\u00f0\7q\2\2\u00f0\16\3\2\2\2\u00f1\u00f2\7f\2\2\u00f2\u00f3"+
		"\7q\2\2\u00f3\u00f4\7w\2\2\u00f4\u00f5\7d\2\2\u00f5\u00f6\7n\2\2\u00f6"+
		"\u00f7\7g\2\2\u00f7\20\3\2\2\2\u00f8\u00f9\7g\2\2\u00f9\u00fa\7n\2\2\u00fa"+
		"\u00fb\7u\2\2\u00fb\u00fc\7g\2\2\u00fc\22\3\2\2\2\u00fd\u00fe\7h\2\2\u00fe"+
		"\u00ff\7n\2\2\u00ff\u0100\7q\2\2\u0100\u0101\7c\2\2\u0101\u0102\7v\2\2"+
		"\u0102\24\3\2\2\2\u0103\u0104\7h\2\2\u0104\u0105\7q\2\2\u0105\u0106\7"+
		"t\2\2\u0106\26\3\2\2\2\u0107\u0108\7i\2\2\u0108\u0109\7q\2\2\u0109\u010a"+
		"\7v\2\2\u010a\u010b\7q\2\2\u010b\30\3\2\2\2\u010c\u010d\7k\2\2\u010d\u010e"+
		"\7h\2\2\u010e\32\3\2\2\2\u010f\u0110\7k\2\2\u0110\u0111\7p\2\2\u0111\u0112"+
		"\7v\2\2\u0112\34\3\2\2\2\u0113\u0114\7t\2\2\u0114\u0115\7g\2\2\u0115\u0116"+
		"\7v\2\2\u0116\u0117\7w\2\2\u0117\u0118\7t\2\2\u0118\u0119\7p\2\2\u0119"+
		"\36\3\2\2\2\u011a\u011b\7u\2\2\u011b\u011c\7k\2\2\u011c\u011d\7|\2\2\u011d"+
		"\u011e\7g\2\2\u011e\u011f\7q\2\2\u011f\u0120\7h\2\2\u0120 \3\2\2\2\u0121"+
		"\u0122\7x\2\2\u0122\u0123\7q\2\2\u0123\u0124\7k\2\2\u0124\u0125\7f\2\2"+
		"\u0125\"\3\2\2\2\u0126\u0127\7y\2\2\u0127\u0128\7j\2\2\u0128\u0129\7k"+
		"\2\2\u0129\u012a\7n\2\2\u012a\u012b\7g\2\2\u012b$\3\2\2\2\u012c\u012d"+
		"\7*\2\2\u012d&\3\2\2\2\u012e\u012f\7+\2\2\u012f(\3\2\2\2\u0130\u0131\7"+
		"]\2\2\u0131*\3\2\2\2\u0132\u0133\7_\2\2\u0133,\3\2\2\2\u0134\u0135\7}"+
		"\2\2\u0135.\3\2\2\2\u0136\u0137\7\177\2\2\u0137\60\3\2\2\2\u0138\u0139"+
		"\7>\2\2\u0139\62\3\2\2\2\u013a\u013b\7>\2\2\u013b\u013c\7?\2\2\u013c\64"+
		"\3\2\2\2\u013d\u013e\7@\2\2\u013e\66\3\2\2\2\u013f\u0140\7@\2\2\u0140"+
		"\u0141\7?\2\2\u01418\3\2\2\2\u0142\u0143\7-\2\2\u0143:\3\2\2\2\u0144\u0145"+
		"\7-\2\2\u0145\u0146\7-\2\2\u0146<\3\2\2\2\u0147\u0148\7/\2\2\u0148>\3"+
		"\2\2\2\u0149\u014a\7/\2\2\u014a\u014b\7/\2\2\u014b@\3\2\2\2\u014c\u014d"+
		"\7,\2\2\u014dB\3\2\2\2\u014e\u014f\7\61\2\2\u014fD\3\2\2\2\u0150\u0151"+
		"\7\'\2\2\u0151F\3\2\2\2\u0152\u0153\7(\2\2\u0153H\3\2\2\2\u0154\u0155"+
		"\7~\2\2\u0155J\3\2\2\2\u0156\u0157\7(\2\2\u0157\u0158\7(\2\2\u0158L\3"+
		"\2\2\2\u0159\u015a\7~\2\2\u015a\u015b\7~\2\2\u015bN\3\2\2\2\u015c\u015d"+
		"\7`\2\2\u015dP\3\2\2\2\u015e\u015f\7#\2\2\u015fR\3\2\2\2\u0160\u0161\7"+
		"\u0080\2\2\u0161T\3\2\2\2\u0162\u0163\7A\2\2\u0163V\3\2\2\2\u0164\u0165"+
		"\7<\2\2\u0165X\3\2\2\2\u0166\u0167\7=\2\2\u0167Z\3\2\2\2\u0168\u0169\7"+
		".\2\2\u0169\\\3\2\2\2\u016a\u016b\7?\2\2\u016b^\3\2\2\2\u016c\u016d\7"+
		",\2\2\u016d\u016e\7?\2\2\u016e`\3\2\2\2\u016f\u0170\7\61\2\2\u0170\u0171"+
		"\7?\2\2\u0171b\3\2\2\2\u0172\u0173\7\'\2\2\u0173\u0174\7?\2\2\u0174d\3"+
		"\2\2\2\u0175\u0176\7-\2\2\u0176\u0177\7?\2\2\u0177f\3\2\2\2\u0178\u0179"+
		"\7/\2\2\u0179\u017a\7?\2\2\u017ah\3\2\2\2\u017b\u017c\7(\2\2\u017c\u017d"+
		"\7?\2\2\u017dj\3\2\2\2\u017e\u017f\7`\2\2\u017f\u0180\7?\2\2\u0180l\3"+
		"\2\2\2\u0181\u0182\7~\2\2\u0182\u0183\7?\2\2\u0183n\3\2\2\2\u0184\u0185"+
		"\7?\2\2\u0185\u0186\7?\2\2\u0186p\3\2\2\2\u0187\u0188\7#\2\2\u0188\u0189"+
		"\7?\2\2\u0189r\3\2\2\2\u018a\u018f\5u;\2\u018b\u018e\5u;\2\u018c\u018e"+
		"\5y=\2\u018d\u018b\3\2\2\2\u018d\u018c\3\2\2\2\u018e\u0191\3\2\2\2\u018f"+
		"\u018d\3\2\2\2\u018f\u0190\3\2\2\2\u0190t\3\2\2\2\u0191\u018f\3\2\2\2"+
		"\u0192\u0195\5w<\2\u0193\u0195\5{>\2\u0194\u0192\3\2\2\2\u0194\u0193\3"+
		"\2\2\2\u0195v\3\2\2\2\u0196\u0197\t\2\2\2\u0197x\3\2\2\2\u0198\u0199\t"+
		"\3\2\2\u0199z\3\2\2\2\u019a\u019b\7^\2\2\u019b\u019c\7w\2\2\u019c\u019d"+
		"\3\2\2\2\u019d\u01a5\5}?\2\u019e\u019f\7^\2\2\u019f\u01a0\7W\2\2\u01a0"+
		"\u01a1\3\2\2\2\u01a1\u01a2\5}?\2\u01a2\u01a3\5}?\2\u01a3\u01a5\3\2\2\2"+
		"\u01a4\u019a\3\2\2\2\u01a4\u019e\3\2\2\2\u01a5|\3\2\2\2\u01a6\u01a7\5"+
		"\u008fH\2\u01a7\u01a8\5\u008fH\2\u01a8\u01a9\5\u008fH\2\u01a9\u01aa\5"+
		"\u008fH\2\u01aa~\3\2\2\2\u01ab\u01ad\5\u0083B\2\u01ac\u01ae\5\u0091I\2"+
		"\u01ad\u01ac\3\2\2\2\u01ad\u01ae\3\2\2\2\u01ae\u01b9\3\2\2\2\u01af\u01b1"+
		"\5\u0085C\2\u01b0\u01b2\5\u0091I\2\u01b1\u01b0\3\2\2\2\u01b1\u01b2\3\2"+
		"\2\2\u01b2\u01b9\3\2\2\2\u01b3\u01b5\5\u0087D\2\u01b4\u01b6\5\u0091I\2"+
		"\u01b5\u01b4\3\2\2\2\u01b5\u01b6\3\2\2\2\u01b6\u01b9\3\2\2\2\u01b7\u01b9"+
		"\5\u0081A\2\u01b8\u01ab\3\2\2\2\u01b8\u01af\3\2\2\2\u01b8\u01b3\3\2\2"+
		"\2\u01b8\u01b7\3\2\2\2\u01b9\u0080\3\2\2\2\u01ba\u01bb\7\62\2\2\u01bb"+
		"\u01bd\t\4\2\2\u01bc\u01be\t\5\2\2\u01bd\u01bc\3\2\2\2\u01be\u01bf\3\2"+
		"\2\2\u01bf\u01bd\3\2\2\2\u01bf\u01c0\3\2\2\2\u01c0\u0082\3\2\2\2\u01c1"+
		"\u01c5\5\u008bF\2\u01c2\u01c4\5y=\2\u01c3\u01c2\3\2\2\2\u01c4\u01c7\3"+
		"\2\2\2\u01c5\u01c3\3\2\2\2\u01c5\u01c6\3\2\2\2\u01c6\u0084\3\2\2\2\u01c7"+
		"\u01c5\3\2\2\2\u01c8\u01cc\7\62\2\2\u01c9\u01cb\5\u008dG\2\u01ca\u01c9"+
		"\3\2\2\2\u01cb\u01ce\3\2\2\2\u01cc\u01ca\3\2\2\2\u01cc\u01cd\3\2\2\2\u01cd"+
		"\u0086\3\2\2\2\u01ce\u01cc\3\2\2\2\u01cf\u01d1\5\u0089E\2\u01d0\u01d2"+
		"\5\u008fH\2\u01d1\u01d0\3\2\2\2\u01d2\u01d3\3\2\2\2\u01d3\u01d1\3\2\2"+
		"\2\u01d3\u01d4\3\2\2\2\u01d4\u0088\3\2\2\2\u01d5\u01d6\7\62\2\2\u01d6"+
		"\u01d7\t\6\2\2\u01d7\u008a\3\2\2\2\u01d8\u01d9\t\7\2\2\u01d9\u008c\3\2"+
		"\2\2\u01da\u01db\t\b\2\2\u01db\u008e\3\2\2\2\u01dc\u01dd\t\t\2\2\u01dd"+
		"\u0090\3\2\2\2\u01de\u01e0\5\u0093J\2\u01df\u01e1\5\u0095K\2\u01e0\u01df"+
		"\3\2\2\2\u01e0\u01e1\3\2\2\2\u01e1\u01ee\3\2\2\2\u01e2\u01e3\5\u0093J"+
		"\2\u01e3\u01e4\5\u0097L\2\u01e4\u01ee\3\2\2\2\u01e5\u01e7\5\u0095K\2\u01e6"+
		"\u01e8\5\u0093J\2\u01e7\u01e6\3\2\2\2\u01e7\u01e8\3\2\2\2\u01e8\u01ee"+
		"\3\2\2\2\u01e9\u01eb\5\u0097L\2\u01ea\u01ec\5\u0093J\2\u01eb\u01ea\3\2"+
		"\2\2\u01eb\u01ec\3\2\2\2\u01ec\u01ee\3\2\2\2\u01ed\u01de\3\2\2\2\u01ed"+
		"\u01e2\3\2\2\2\u01ed\u01e5\3\2\2\2\u01ed\u01e9\3\2\2\2\u01ee\u0092\3\2"+
		"\2\2\u01ef\u01f0\t\n\2\2\u01f0\u0094\3\2\2\2\u01f1\u01f2\t\13\2\2\u01f2"+
		"\u0096\3\2\2\2\u01f3\u01f4\7n\2\2\u01f4\u01f8\7n\2\2\u01f5\u01f6\7N\2"+
		"\2\u01f6\u01f8\7N\2\2\u01f7\u01f3\3\2\2\2\u01f7\u01f5\3\2\2\2\u01f8\u0098"+
		"\3\2\2\2\u01f9\u01fc\5\u009bN\2\u01fa\u01fc\5\u009dO\2\u01fb\u01f9\3\2"+
		"\2\2\u01fb\u01fa\3\2\2\2\u01fc\u009a\3\2\2\2\u01fd\u01ff\5\u009fP\2\u01fe"+
		"\u0200\5\u00a1Q\2\u01ff\u01fe\3\2\2\2\u01ff\u0200\3\2\2\2\u0200\u0202"+
		"\3\2\2\2\u0201\u0203\5\u00adW\2\u0202\u0201\3\2\2\2\u0202\u0203\3\2\2"+
		"\2\u0203\u020a\3\2\2\2\u0204\u0205\5\u00a5S\2\u0205\u0207\5\u00a1Q\2\u0206"+
		"\u0208\5\u00adW\2\u0207\u0206\3\2\2\2\u0207\u0208\3\2\2\2\u0208\u020a"+
		"\3\2\2\2\u0209\u01fd\3\2\2\2\u0209\u0204\3\2\2\2\u020a\u009c\3\2\2\2\u020b"+
		"\u020e\5\u0089E\2\u020c\u020f\5\u00a7T\2\u020d\u020f\5\u00abV\2\u020e"+
		"\u020c\3\2\2\2\u020e\u020d\3\2\2\2\u020f\u0210\3\2\2\2\u0210\u0212\5\u00a9"+
		"U\2\u0211\u0213\5\u00adW\2\u0212\u0211\3\2\2\2\u0212\u0213\3\2\2\2\u0213"+
		"\u009e\3\2\2\2\u0214\u0216\5\u00a5S\2\u0215\u0214\3\2\2\2\u0215\u0216"+
		"\3\2\2\2\u0216\u0217\3\2\2\2\u0217\u0218\7\60\2\2\u0218\u021d\5\u00a5"+
		"S\2\u0219\u021a\5\u00a5S\2\u021a\u021b\7\60\2\2\u021b\u021d\3\2\2\2\u021c"+
		"\u0215\3\2\2\2\u021c\u0219\3\2\2\2\u021d\u00a0\3\2\2\2\u021e\u0220\t\f"+
		"\2\2\u021f\u0221\5\u00a3R\2\u0220\u021f\3\2\2\2\u0220\u0221\3\2\2\2\u0221"+
		"\u0222\3\2\2\2\u0222\u0223\5\u00a5S\2\u0223\u00a2\3\2\2\2\u0224\u0225"+
		"\t\r\2\2\u0225\u00a4\3\2\2\2\u0226\u0228\5y=\2\u0227\u0226\3\2\2\2\u0228"+
		"\u0229\3\2\2\2\u0229\u0227\3\2\2\2\u0229\u022a\3\2\2\2\u022a\u00a6\3\2"+
		"\2\2\u022b\u022d\5\u00abV\2\u022c\u022b\3\2\2\2\u022c\u022d\3\2\2\2\u022d"+
		"\u022e\3\2\2\2\u022e\u022f\7\60\2\2\u022f\u0234\5\u00abV\2\u0230\u0231"+
		"\5\u00abV\2\u0231\u0232\7\60\2\2\u0232\u0234\3\2\2\2\u0233\u022c\3\2\2"+
		"\2\u0233\u0230\3\2\2\2\u0234\u00a8\3\2\2\2\u0235\u0237\t\16\2\2\u0236"+
		"\u0238\5\u00a3R\2\u0237\u0236\3\2\2\2\u0237\u0238\3\2\2\2\u0238\u0239"+
		"\3\2\2\2\u0239\u023a\5\u00a5S\2\u023a\u00aa\3\2\2\2\u023b\u023d\5\u008f"+
		"H\2\u023c\u023b\3\2\2\2\u023d\u023e\3\2\2\2\u023e\u023c\3\2\2\2\u023e"+
		"\u023f\3\2\2\2\u023f\u00ac\3\2\2\2\u0240\u0241\t\17\2\2\u0241\u00ae\3"+
		"\2\2\2\u0242\u0243\7)\2\2\u0243\u0244\5\u00b1Y\2\u0244\u0245\7)\2\2\u0245"+
		"\u0259\3\2\2\2\u0246\u0247\7N\2\2\u0247\u0248\7)\2\2\u0248\u0249\3\2\2"+
		"\2\u0249\u024a\5\u00b1Y\2\u024a\u024b\7)\2\2\u024b\u0259\3\2\2\2\u024c"+
		"\u024d\7w\2\2\u024d\u024e\7)\2\2\u024e\u024f\3\2\2\2\u024f\u0250\5\u00b1"+
		"Y\2\u0250\u0251\7)\2\2\u0251\u0259\3\2\2\2\u0252\u0253\7W\2\2\u0253\u0254"+
		"\7)\2\2\u0254\u0255\3\2\2\2\u0255\u0256\5\u00b1Y\2\u0256\u0257\7)\2\2"+
		"\u0257\u0259\3\2\2\2\u0258\u0242\3\2\2\2\u0258\u0246\3\2\2\2\u0258\u024c"+
		"\3\2\2\2\u0258\u0252\3\2\2\2\u0259\u00b0\3\2\2\2\u025a\u025c\5\u00b3Z"+
		"\2\u025b\u025a\3\2\2\2\u025c\u025d\3\2\2\2\u025d\u025b\3\2\2\2\u025d\u025e"+
		"\3\2\2\2\u025e\u00b2\3\2\2\2\u025f\u0262\n\20\2\2\u0260\u0262\5\u00b5"+
		"[\2\u0261\u025f\3\2\2\2\u0261\u0260\3\2\2\2\u0262\u00b4\3\2\2\2\u0263"+
		"\u0268\5\u00b7\\\2\u0264\u0268\5\u00b9]\2\u0265\u0268\5\u00bb^\2\u0266"+
		"\u0268\5{>\2\u0267\u0263\3\2\2\2\u0267\u0264\3\2\2\2\u0267\u0265\3\2\2"+
		"\2\u0267\u0266\3\2\2\2\u0268\u00b6\3\2\2\2\u0269\u026a\7^\2\2\u026a\u026b"+
		"\t\21\2\2\u026b\u00b8\3\2\2\2\u026c\u026d\7^\2\2\u026d\u026f\5\u008dG"+
		"\2\u026e\u0270\5\u008dG\2\u026f\u026e\3\2\2\2\u026f\u0270\3\2\2\2\u0270"+
		"\u0272\3\2\2\2\u0271\u0273\5\u008dG\2\u0272\u0271\3\2\2\2\u0272\u0273"+
		"\3\2\2\2\u0273\u00ba\3\2\2\2\u0274\u0275\7^\2\2\u0275\u0276\7z\2\2\u0276"+
		"\u0278\3\2\2\2\u0277\u0279\5\u008fH\2\u0278\u0277\3\2\2\2\u0279\u027a"+
		"\3\2\2\2\u027a\u0278\3\2\2\2\u027a\u027b\3\2\2\2\u027b\u00bc\3\2\2\2\u027c"+
		"\u027e\5\u00bf`\2\u027d\u027c\3\2\2\2\u027d\u027e\3\2\2\2\u027e\u027f"+
		"\3\2\2\2\u027f\u0281\7$\2\2\u0280\u0282\5\u00c1a\2\u0281\u0280\3\2\2\2"+
		"\u0281\u0282\3\2\2\2\u0282\u0283\3\2\2\2\u0283\u0284\7$\2\2\u0284\u00be"+
		"\3\2\2\2\u0285\u0286\7w\2\2\u0286\u0289\7:\2\2\u0287\u0289\t\22\2\2\u0288"+
		"\u0285\3\2\2\2\u0288\u0287\3\2\2\2\u0289\u00c0\3\2\2\2\u028a\u028c\5\u00c3"+
		"b\2\u028b\u028a\3\2\2\2\u028c\u028d\3\2\2\2\u028d\u028b\3\2\2\2\u028d"+
		"\u028e\3\2\2\2\u028e\u00c2\3\2\2\2\u028f\u0297\n\23\2\2\u0290\u0297\5"+
		"\u00b5[\2\u0291\u0292\7^\2\2\u0292\u0297\7\f\2\2\u0293\u0294\7^\2\2\u0294"+
		"\u0295\7\17\2\2\u0295\u0297\7\f\2\2\u0296\u028f\3\2\2\2\u0296\u0290\3"+
		"\2\2\2\u0296\u0291\3\2\2\2\u0296\u0293\3\2\2\2\u0297\u00c4\3\2\2\2\u0298"+
		"\u029a\t\24\2\2\u0299\u0298\3\2\2\2\u029a\u029b\3\2\2\2\u029b\u0299\3"+
		"\2\2\2\u029b\u029c\3\2\2\2\u029c\u029d\3\2\2\2\u029d\u029e\bc\2\2\u029e"+
		"\u00c6\3\2\2\2\u029f\u02a1\7\17\2\2\u02a0\u02a2\7\f\2\2\u02a1\u02a0\3"+
		"\2\2\2\u02a1\u02a2\3\2\2\2\u02a2\u02a5\3\2\2\2\u02a3\u02a5\7\f\2\2\u02a4"+
		"\u029f\3\2\2\2\u02a4\u02a3\3\2\2\2\u02a5\u02a6\3\2\2\2\u02a6\u02a7\bd"+
		"\2\2\u02a7\u00c8\3\2\2\2\u02a8\u02a9\7\61\2\2\u02a9\u02aa\7,\2\2\u02aa"+
		"\u02ae\3\2\2\2\u02ab\u02ad\13\2\2\2\u02ac\u02ab\3\2\2\2\u02ad\u02b0\3"+
		"\2\2\2\u02ae\u02af\3\2\2\2\u02ae\u02ac\3\2\2\2\u02af\u02b1\3\2\2\2\u02b0"+
		"\u02ae\3\2\2\2\u02b1\u02b2\7,\2\2\u02b2\u02b3\7\61\2\2\u02b3\u02b4\3\2"+
		"\2\2\u02b4\u02b5\be\2\2\u02b5\u00ca\3\2\2\2\u02b6\u02b7\7\61\2\2\u02b7"+
		"\u02b8\7\61\2\2\u02b8\u02bc\3\2\2\2\u02b9\u02bb\n\25\2\2\u02ba\u02b9\3"+
		"\2\2\2\u02bb\u02be\3\2\2\2\u02bc\u02ba\3\2\2\2\u02bc\u02bd\3\2\2\2\u02bd"+
		"\u02bf\3\2\2\2\u02be\u02bc\3\2\2\2\u02bf\u02c0\bf\2\2\u02c0\u00cc\3\2"+
		"\2\2\64\2\u018d\u018f\u0194\u01a4\u01ad\u01b1\u01b5\u01b8\u01bf\u01c5"+
		"\u01cc\u01d3\u01e0\u01e7\u01eb\u01ed\u01f7\u01fb\u01ff\u0202\u0207\u0209"+
		"\u020e\u0212\u0215\u021c\u0220\u0229\u022c\u0233\u0237\u023e\u0258\u025d"+
		"\u0261\u0267\u026f\u0272\u027a\u027d\u0281\u0288\u028d\u0296\u029b\u02a1"+
		"\u02a4\u02ae\u02bc\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}