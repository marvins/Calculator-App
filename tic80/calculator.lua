-- title:  Calculator
-- author: Marvin Smith
-- desc:   Simple calculator solver
-- script: lua

--input_str = "3 + 4 x 2 / (1 - 5 ) ^2 ^2"
input_str = "3 + 4 - 2.3"

cursor_x = 0
cursor_y = 0

COLOR_RED   =  2
COLOR_LBLUE = 10
COLOR_WHITE = 12

CELL_H = 8
CELL_W = 8

TK_OP_PLUS  = 1
TK_OP_MINUS = 2
TK_OP_TIMES = 3
TK_OP_DIV   = 4
TK_OP_POWER = 5
TK_OP_LPAR  = 6
TK_OP_RPAR  = 7
TK_NUMBER   = 8

LEFT = 0
RIGHT = 1

function Precedence( operator )
    if ( operator == TK_OP_PLUS ) then
        return 2
    elseif ( operator == TK_OP_MINUS ) then
        return 2
    elseif ( operator == TK_OP_TIMES ) then
        return 3
    elseif ( operator == TK_OP_DIV ) then
        return 3
    elseif ( operator == TK_OP_POWER ) then
        return 4
    end
end

function Associativity( operator )
    if ( operator == TK_OP_PLUS ) then
        return LEFT
    elseif ( operator == TK_OP_MINUS ) then
        return LEFT
    elseif ( operator == TK_OP_TIMES ) then
        return LEFT
    elseif ( operator == TK_OP_DIV ) then
        return LEFT
    elseif ( operator == TK_OP_POWER ) then
        return RIGHT
    end
end

function Print( text, cx, cy, color )
    print( text, cx, cy, color ) 
end

function Tokenize( input_str )
    tokens = {}
    for str in string.gmatch( input_str, "%S+" )
    do
        -- Check for + operator
        local value = nil
        if ( str == "+" ) then
            value = { TK_OP_PLUS }
        elseif( str == "-" ) then  
            value = { TK_OP_MINUS }
        elseif( str == "x" ) then
            value = { TK_OP_TIMES }
        elseif( str == "/" ) then
            value = { TK_OP_DIV }
        else
            value = { TK_NUMBER, tonumber(str) }
        end
        table.insert( tokens, value )
    end    
   
    return tokens
end

function Infix2RPN_Shunting_Yard( tokens )

    -- output queue
    output_queue = {}
    local oque_idx = 1

    -- operator stack
    operator_stack = {}
    local opstack_idx = 1

    -- Iterate over each token
    for idx = 1, #tokens, 1 do

        -- If the token is a number, add to the output queue
        if ( ( #tokens[idx] > 1 ) and ( tokens[idx][1] == TK_NUMBER ) ) then
            table.insert( output_queue, tokens[idx] )

        -- If the token is a left parenthesis
        elseif ( tokens[idx][1] == TK_OP_LPAR ) then
            operator_stack[opstack_idx] = tokens[idx]
            opstack_idx = opstack_idx + 1
        
            -- If the token is an operator, 
        else
            -- If the token is an operator, check the top of the operator stack
            --   1.  The operator is not left parenthesis
            --   2.  The operator has higher precedence than the token operator
            --   3.  The operators are both equal precedence and the current token is left associative
            
            while( ( #operator_stack >= opstack_idx ) and 
                   ( operator_stack[opstack_idx][1] != TK_OP_LPAR ) and 
                   ( ( Precedence( tokens[idx][1] ) > Precedence( operator_stack[opstack_idx][1] ) ) 
                     or 
                     ( ( Precedence( tokens[idx][1] ) == Precedence( operator_stack[opstack_idx][1] ) ) and Associativity( tokens[idx][1] ) == LEFT ) ) 
            do
                output_queue[oque_idx] = operator_stack[opstack_idx]
                oque_idx = oque_idx + 1
                operator_stack[opstack_idx] = tokens[idx]
            end
        end
    end
end

function TIC()

    -- clear screen
    cls()
    
    -- Draw interface
    rect( 0, 0, 100, 100, COLOR_RED )

    -- Tokenize the input string
    tokens = Tokenize( input_str )
    
    -- Print Tokens
    local i=0
    for _, v in ipairs( tokens ) 
      do 
        if( #v > 1 ) then
            Print( string.format( "%d, %d %f", #v, v[1], v[2] ), 5, i * 7 + 3, COLOR_LBLUE )
        else
            Print( string.format( "%d, %d", #v, v[1] ), 5, i * 7 + 3, COLOR_LBLUE )
        end
        i = i + 1
    end
    
    -- Convert to RPN
    tokens = Infix2RPN_Shunting_Yard( tokens )
      
    -- Compute the result
    result = "?"

    -- Print the input equation
    Print( input_str .. "=" .. result, 10, 130, COLOR_WHITE )
end

-- <TILES>
-- 001:eccccccccc888888caaaaaaaca888888cacccccccacc0ccccacc0ccccacc0ccc
-- 002:ccccceee8888cceeaaaa0cee888a0ceeccca0ccc0cca0c0c0cca0c0c0cca0c0c
-- 003:eccccccccc888888caaaaaaaca888888cacccccccacccccccacc0ccccacc0ccc
-- 004:ccccceee8888cceeaaaa0cee888a0ceeccca0cccccca0c0c0cca0c0c0cca0c0c
-- 017:cacccccccaaaaaaacaaacaaacaaaaccccaaaaaaac8888888cc000cccecccccec
-- 018:ccca00ccaaaa0ccecaaa0ceeaaaa0ceeaaaa0cee8888ccee000cceeecccceeee
-- 019:cacccccccaaaaaaacaaacaaacaaaaccccaaaaaaac8888888cc000cccecccccec
-- 020:ccca00ccaaaa0ccecaaa0ceeaaaa0ceeaaaa0cee8888ccee000cceeecccceeee
-- </TILES>

-- <WAVES>
-- 000:00000000ffffffff00000000ffffffff
-- 001:0123456789abcdeffedcba9876543210
-- 002:0123456789abcdef0123456789abcdef
-- </WAVES>

-- <SFX>
-- 000:000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000304000000000
-- </SFX>

-- <TRACKS>
-- 000:100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
-- </TRACKS>

-- <PALETTE>
-- 000:1a1c2c5d275db13e53ef7d57ffcd75a7f07038b76425717929366f3b5dc941a6f673eff7f4f4f494b0c2566c86333c57
-- </PALETTE>

