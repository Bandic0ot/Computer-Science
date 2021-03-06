/*
 * ParserRule.java - Parser rule for the token marker
 * :tabSize=8:indentSize=8:noTabs=false:
 * :folding=explicit:collapseFolds=1:
 *
 * Copyright (C) 1999 mike dillon
 * Portions copyright (C) 2002 Slava Pestov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

package org.gjt.sp.jedit.syntax;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;

/**
 * A parser rule.
 * @author mike dillon, Slava Pestov
 * @version $Id: ParserRule.java 8103 2006-11-21 00:03:41Z vampire0 $
 */
public class ParserRule
{

	//{{{ Major actions
	public static final int MAJOR_ACTIONS = 0x000000FF;
	public static final int SEQ = 0;
	public static final int SPAN = 1 << 1;
	public static final int MARK_PREVIOUS = 1 << 2;
	public static final int MARK_FOLLOWING = 1 << 3;
	public static final int EOL_SPAN = 1 << 4;
	//}}}

	//{{{ Action hints
	public static final int ACTION_HINTS = 0x0000FF00;
	public static final int EXCLUDE_MATCH = 1 << 8;
	public static final int NO_LINE_BREAK = 1 << 9;
	public static final int NO_WORD_BREAK = 1 << 10;
	public static final int IS_ESCAPE = 1 << 11;
	public static final int NO_ESCAPE = 1 << 12;
	public static final int REGEXP = 1 << 13;
	//}}}

	//{{{ Position match hints
	public static final int AT_LINE_START = 1 << 1;
	public static final int AT_WHITESPACE_END = 1 << 2;
	public static final int AT_WORD_START = 1 << 3;
	//}}}

	//{{{ Instance variables
	public final String hashChar;
	/** This is hashChar.toUpperCase() because it's often used like that. */
	public final String upHashChar;
	public final char[] hashChars;
	/** This is for (int i=0 ; i&lt;hashChars.length ; i++) { upHashChars[i] = Character.toUpperCase(hashChars[i]) } because it's often used like that. */
	public final char[] upHashChars;
	public final int startPosMatch;
	public final char[] start;
	public final Pattern startRegexp;

	public final int endPosMatch;
	public final char[] end;

	public final int action;
	public final byte token;

	public ParserRuleSet delegate;

	/**
	* @deprecated As the linking between rules is not anymore done within the rule but external. See {@link ParserRuleSet#getRules(Character)}
	*/
	public ParserRule next;
	//}}}

	//{{{ createSequenceRule() method
	public static final ParserRule createSequenceRule(
		int posMatch, String seq, ParserRuleSet delegate, byte id)
	{
		return new ParserRule(SEQ, seq.substring(0,1),
			posMatch, seq.toCharArray(), null,
			0, null, delegate, id);
	} //}}}

	//{{{ createRegexpSequenceRule() method
	/**
	 * @deprecated Use {@link #createRegexpSequenceRule(String,int,String,ParserRuleSet,byte,boolean)} instead
	 */
	public static final ParserRule createRegexpSequenceRule(
		char hashChar, int posMatch, String seq,
		ParserRuleSet delegate, byte id, boolean ignoreCase)
		throws PatternSyntaxException
	{
		return createRegexpSequenceRule(String.valueOf(hashChar), posMatch,
			seq, delegate, id, ignoreCase);
	} //}}}

	//{{{ createRegexpSequenceRule() method
	public static final ParserRule createRegexpSequenceRule(
		String hashChar, int posMatch, String seq,
		ParserRuleSet delegate, byte id, boolean ignoreCase)
		throws PatternSyntaxException
	{
		return new ParserRule(SEQ | REGEXP, hashChar, posMatch,
			null, Pattern.compile(seq,(ignoreCase ? Pattern.CASE_INSENSITIVE : 0)),
			0, null, delegate, id);
	} //}}}

	//{{{ createRegexpSequenceRule() method
	public static final ParserRule createRegexpSequenceRule(
		int posMatch, char[] hashChars, String seq,
		ParserRuleSet delegate, byte id, boolean ignoreCase)
		throws PatternSyntaxException
	{
		return new ParserRule(hashChars, SEQ | REGEXP, posMatch,
			null, Pattern.compile(seq,(ignoreCase ? Pattern.CASE_INSENSITIVE : 0)),
			0, null, delegate, id);
	} //}}}

	//{{{ createSpanRule() method
	public static final ParserRule createSpanRule(
		int startPosMatch, String start, int endPosMatch, String end,
		ParserRuleSet delegate, byte id, boolean excludeMatch,
		boolean noLineBreak, boolean noWordBreak, boolean noEscape)
	{
		int ruleAction = SPAN |
			((noLineBreak) ? NO_LINE_BREAK : 0) |
			((excludeMatch) ? EXCLUDE_MATCH : 0) |
			((noWordBreak) ? NO_WORD_BREAK : 0) |
			((noEscape) ? NO_ESCAPE : 0);

		return new ParserRule(ruleAction, start.substring(0,1), startPosMatch,
			start.toCharArray(), null,
			endPosMatch, end.toCharArray(),
			delegate, id);
	} //}}}

	//{{{ createRegexpSpanRule() method
	/**
	 * @deprecated Use {@link #createRegexpSpanRule(String,int,String,int,String,ParserRuleSet,byte,boolean,boolean,boolean,boolean,boolean)} instead
	 */
	public static final ParserRule createRegexpSpanRule(
		char hashChar, int startPosMatch, String start,
		int endPosMatch, String end, ParserRuleSet delegate, byte id,
		boolean excludeMatch, boolean noLineBreak, boolean noWordBreak,
		boolean ignoreCase, boolean noEscape)
		throws PatternSyntaxException
	{
		return createRegexpSpanRule(String.valueOf(hashChar),startPosMatch,
			start,endPosMatch,end,delegate,id,excludeMatch,
			noLineBreak,noWordBreak,ignoreCase,noEscape);
	} //}}}

	//{{{ createRegexpSpanRule() method
	public static final ParserRule createRegexpSpanRule(
		String hashChar, int startPosMatch, String start,
		int endPosMatch, String end, ParserRuleSet delegate, byte id,
		boolean excludeMatch, boolean noLineBreak, boolean noWordBreak,
		boolean ignoreCase, boolean noEscape)
		throws PatternSyntaxException
	{
		int ruleAction = SPAN | REGEXP |
			((noLineBreak) ? NO_LINE_BREAK : 0) |
			((excludeMatch) ? EXCLUDE_MATCH : 0) |
			((noWordBreak) ? NO_WORD_BREAK : 0) |
			((noEscape) ? NO_ESCAPE : 0);

		return new ParserRule(ruleAction, hashChar, startPosMatch, null,
			Pattern.compile(start,(ignoreCase ? Pattern.CASE_INSENSITIVE : 0)),
			endPosMatch, end.toCharArray(), delegate, id);
	} //}}}

	//{{{ createRegexpSpanRule() method
	public static final ParserRule createRegexpSpanRule(
		int startPosMatch, char[] hashChars, String start,
		int endPosMatch, String end, ParserRuleSet delegate, byte id,
		boolean excludeMatch, boolean noLineBreak, boolean noWordBreak,
		boolean ignoreCase, boolean noEscape)
		throws PatternSyntaxException
	{
		int ruleAction = SPAN | REGEXP |
			((noLineBreak) ? NO_LINE_BREAK : 0) |
			((excludeMatch) ? EXCLUDE_MATCH : 0) |
			((noWordBreak) ? NO_WORD_BREAK : 0) |
			((noEscape) ? NO_ESCAPE : 0);

		return new ParserRule(hashChars, ruleAction, startPosMatch, null,
			Pattern.compile(start,(ignoreCase ? Pattern.CASE_INSENSITIVE : 0)),
			endPosMatch, end.toCharArray(), delegate, id);
	} //}}}

	//{{{ createEOLSpanRule() method
	public static final ParserRule createEOLSpanRule(
		int posMatch, String seq, ParserRuleSet delegate, byte id,
		boolean excludeMatch)
	{
		int ruleAction = EOL_SPAN |
			((excludeMatch) ? EXCLUDE_MATCH : 0)
			| NO_LINE_BREAK;

		return new ParserRule(ruleAction, seq.substring(0,1), posMatch,
			seq.toCharArray(), null, 0, null,
			delegate, id);
	} //}}}

	//{{{ createRegexpEOLSpanRule() method
	/**
	 * @deprecated Use {@link #createRegexpEOLSpanRule(String,int,String,ParserRuleSet,byte,boolean,boolean)} instead
	 */
	public static final ParserRule createRegexpEOLSpanRule(
		char hashChar, int posMatch, String seq, ParserRuleSet delegate,
		byte id, boolean excludeMatch, boolean ignoreCase)
		throws PatternSyntaxException
	{
		return createRegexpEOLSpanRule(String.valueOf(hashChar),
			posMatch,seq,delegate,id,excludeMatch,ignoreCase);
	} //}}}

	//{{{ createRegexpEOLSpanRule() method
	public static final ParserRule createRegexpEOLSpanRule(
		String hashChar, int posMatch, String seq, ParserRuleSet delegate,
		byte id, boolean excludeMatch, boolean ignoreCase)
		throws PatternSyntaxException
	{
		int ruleAction = EOL_SPAN | REGEXP |
			((excludeMatch) ? EXCLUDE_MATCH : 0)
			| NO_LINE_BREAK;

		return new ParserRule(ruleAction, hashChar, posMatch,
			null, Pattern.compile(seq,(ignoreCase ? Pattern.CASE_INSENSITIVE : 0)),
			0, null, delegate, id);
	} //}}}

	//{{{ createRegexpEOLSpanRule() method
	public static final ParserRule createRegexpEOLSpanRule(
		int posMatch, char[] hashChars, String seq, ParserRuleSet delegate,
		byte id, boolean excludeMatch, boolean ignoreCase)
		throws PatternSyntaxException
	{
		int ruleAction = EOL_SPAN | REGEXP |
			((excludeMatch) ? EXCLUDE_MATCH : 0)
			| NO_LINE_BREAK;

		return new ParserRule(hashChars, ruleAction, posMatch,
			null, Pattern.compile(seq,(ignoreCase ? Pattern.CASE_INSENSITIVE : 0)),
			0, null, delegate, id);
	} //}}}

	//{{{ createMarkFollowingRule() method
	public static final ParserRule createMarkFollowingRule(
		int posMatch, String seq, byte id, boolean excludeMatch)
	{
		int ruleAction = MARK_FOLLOWING |
			((excludeMatch) ? EXCLUDE_MATCH : 0);

		return new ParserRule(ruleAction, seq.substring(0,1), posMatch,
			seq.toCharArray(), null, 0, null, null, id);
	} //}}}

	//{{{ createMarkPreviousRule() method
	public static final ParserRule createMarkPreviousRule(
		int posMatch, String seq, byte id, boolean excludeMatch)
	{
		int ruleAction = MARK_PREVIOUS |
			((excludeMatch) ? EXCLUDE_MATCH : 0);

		return new ParserRule(ruleAction, seq.substring(0,1), posMatch,
			seq.toCharArray(), null, 0, null, null, id);
	} //}}}

	//{{{ createEscapeRule() method
	public static final ParserRule createEscapeRule(String seq)
	{
		int ruleAction = IS_ESCAPE;

		return new ParserRule(ruleAction, seq.substring(0,1),
			0, seq.toCharArray(), null, 0, null,
			null, Token.NULL);
	} //}}}

	//{{{ toString() method
	public String toString()
	{
		StringBuffer result = new StringBuffer();
		result.append(getClass().getName()).append("[action=");
		switch (action & MAJOR_ACTIONS)
		{
			case SEQ: result.append("SEQ"); break;
			case SPAN: result.append("SPAN"); break;
			case MARK_PREVIOUS: result.append("MARK_PREVIOUS"); break;
			case MARK_FOLLOWING: result.append("MARK_FOLLOWING"); break;
			case EOL_SPAN: result.append("EOL_SPAN"); break;
			default: result.append("UNKNOWN"); break;
		}
		int actionHints = action & ACTION_HINTS;
		result.append("[EXCLUDE_MATCH=").append((actionHints & EXCLUDE_MATCH) != 0);
		result.append(",NO_LINE_BREAK=").append((actionHints & NO_LINE_BREAK) != 0);
		result.append(",NO_WORD_BREAK=").append((actionHints & NO_WORD_BREAK) != 0);
		result.append(",IS_ESCAPE=").append((actionHints & IS_ESCAPE) != 0);
		result.append(",NO_ESCAPE=").append((actionHints & NO_ESCAPE) != 0);
		result.append(",REGEXP=").append((actionHints & REGEXP) != 0);
		result.append("],hashChar=").append(hashChar);
		result.append(",upHashChar=").append(upHashChar);
		result.append(",hashChars=").append(Arrays.toString(hashChars));
		result.append(",upHashChars=").append(Arrays.toString(upHashChars));
		result.append(",startPosMatch=");
		result.append("[AT_LINE_START=").append((startPosMatch & AT_LINE_START) != 0);
		result.append(",AT_WHITESPACE_END=").append((startPosMatch & AT_WHITESPACE_END) != 0);
		result.append(",AT_WORD_START=").append((startPosMatch & AT_WORD_START) != 0);
		result.append("],start=").append(null==start?null:String.valueOf(start));
		result.append(",startRegexp=").append(startRegexp);
		result.append(",endPosMatch=");
		result.append("[AT_LINE_START=").append((endPosMatch & AT_LINE_START) != 0);
		result.append(",AT_WHITESPACE_END=").append((endPosMatch & AT_WHITESPACE_END) != 0);
		result.append(",AT_WORD_START=").append((endPosMatch & AT_WORD_START) != 0);
		result.append("],end=").append(null==end?null:String.valueOf(end));
		result.append(",delegate=").append(delegate);
		result.append(",token=").append(Token.tokenToString(token)).append(']');
		return result.toString();
	} //}}}

	//{{{ Private members
	private ParserRule(int action, String hashChar,
		int startPosMatch, char[] start, Pattern startRegexp,
		int endPosMatch, char[] end,
		ParserRuleSet delegate, byte token)
	{
		this.action = action;
		this.hashChar = hashChar;
		this.upHashChar = null == hashChar ? null : hashChar.toUpperCase();
		this.hashChars = null;
		this.upHashChars = null;
		this.startPosMatch = startPosMatch;
		this.start = start;
		this.startRegexp = startRegexp;
		this.endPosMatch = endPosMatch;
		this.end = end;
		this.delegate = delegate;
		this.token = token;

		if(this.delegate == null)
		{
			if((action & MAJOR_ACTIONS) != SEQ)
			{
				this.delegate = ParserRuleSet.getStandardRuleSet(token);
			}
		}
	}

	private ParserRule(char[] hashChars, int action,
		int startPosMatch, char[] start, Pattern startRegexp,
		int endPosMatch, char[] end,
		ParserRuleSet delegate, byte token)
	{
		this.action = action;
		this.hashChar = null;
		this.upHashChar = null;
		Set<Character> hashCharsSet = new HashSet<Character>();
		for (char c : hashChars)
		{
			hashCharsSet.add(c);
		}
		this.hashChars = new char[hashCharsSet.size()];
		int i = 0;
		for (Character c : hashCharsSet)
		{
			this.hashChars[i++] = c;
		}
		hashCharsSet = new HashSet<Character>();
		for (char c : hashChars)
		{
			hashCharsSet.add(Character.toUpperCase(c));
		}
		this.upHashChars = new char[hashCharsSet.size()];
		i = 0;
		for (Character c : hashCharsSet)
		{
			this.upHashChars[i++] = c;
		}
		this.startPosMatch = startPosMatch;
		this.start = start;
		this.startRegexp = startRegexp;
		this.endPosMatch = endPosMatch;
		this.end = end;
		this.delegate = delegate;
		this.token = token;

		if(this.delegate == null)
		{
			if((action & MAJOR_ACTIONS) != SEQ)
			{
				this.delegate = ParserRuleSet.getStandardRuleSet(token);
			}
		}
	} //}}}
}
