-- title:  Calculator
-- author: Marvin Smith
-- desc:   Simple calculator solver
-- script: lua

console_text = "3 + 4 x 2"

cursor_x = 0
cursor_y = 0

CURSOR_LOCK = false

COLOR_RED   =  2
COLOR_LBLUE = 10
COLOR_WHITE = 12

CELL_H = 8
CELL_W = 8

CURRENT_PAGE = 1

TK_OP_PLUS    = 1
TK_OP_MINUS   = 2
TK_OP_TIMES   = 3
TK_OP_DIV     = 4
TK_OP_POWER   = 5
TK_OP_LPAR    = 6
TK_OP_RPAR    = 7
TK_NUMBER     = 8
TK_TASK_QUIT  = 9
TK_TASK_CLR   = 10
TK_TASK_SOLVE = 11
TK_TASK_PGDN  = 12
TK_TASK_PGUP  = 13
TK_FUNC_TAN   = 14
TK_FUNC_ATN   = 15
TK_FUNC_SIN   = 16
TK_FUNC_ASN   = 17
TK_FUNC_COS   = 18
TK_FUNC_ACS   = 19
TK_FUNC_UNK   = 20


SPR_0      = 16
SPR_9      = 25
SPR_DOT    = 26
SPR_BLANK  = 27
SPR_A      = 32
SPR_Z      = 57
SPR_PLUS   = 64
SPR_MINUS  = 65
SPR_DIVIDE = 66
SPR_TIMES  = 67
SPR_POWER  = 68
SPR_START  = 69
SPR_LPARAM = 70
SPR_RPARAM = 71

-- Screen Button Bounds
SCR_KEY_CLR = {   6, 116,  34,  130, "CLR",  1, { TK_TASK_CLR } }
SCR_KEY_0   = {  36, 116,  66,  130, "0",    1, { TK_NUMBER, "0" } }
SCR_KEY_DOT = {  68, 116,  98,  130, ".",    1, { TK_NUMBER, "." } }
SCR_KEY_DIV = { 100, 116, 130,  130, "/",    1, { TK_OP_DIV, "/" } }
SCR_KEY_LPM = { 132, 116, 162,  130, "(",    1, { TK_OP_LPAR, "(" } }
SCR_KEY_RPM = { 164, 116, 194,  130, ")",    1, { TK_OP_RPAR, ")" } }
SCR_KEY_QUT = { 196, 116, 234,  130, "QUIT", 0, { TK_TASK_QUIT } }

SCR_KEY_1   = {   6, 102,  34,  114, "1",    1, { TK_NUMBER, "1" } }
SCR_KEY_2   = {  36, 102,  66,  114, "2",    1, { TK_NUMBER, "2" } }
SCR_KEY_3   = {  68, 102,  98,  114, "3",    1, { TK_NUMBER, "3" } }
SCR_KEY_TIM = { 100, 102, 130,  114, "x",    1, { TK_OP_TIMES, "x" } }
SCR_KEY_TAN = { 132, 102, 162,  114, "TAN",  1, { TK_FUNC_TAN, "TAN" } }
SCR_KEY_ATN = { 164, 102, 194,  114, "ATN",  1, { TK_FUNC_ATN, "ATAN" } }
SCR_KEY_SLV = { 196, 102, 234,  114, "SLV",  1, { TK_TASK_SOLVE } }

SCR_KEY_4   = {   6,  86,  34,   96, "4",    1, { TK_NUMBER, "4" } }
SCR_KEY_5   = {  36,  86,  66,   96, "5",    1, { TK_NUMBER, "5" } }
SCR_KEY_6   = {  68,  86,  98,   96, "6",    1, { TK_NUMBER, "6" } }
SCR_KEY_SUB = { 100,  86, 130,   96, "-",    1, { TK_OP_MINUS, "-" } }
SCR_KEY_COS = { 132,  86, 162,   96, "COS",  1, { TK_FUNC_COS, "COS" } }
SCR_KEY_ACS = { 164,  86, 194,   96, "ACS",  1, { TK_FUNC_ACS, "ACOS" } }
SCR_KEY_PGD = { 196,  86, 234,   96, "PGD",  0, { TK_TASK_PGDN } }

SCR_KEY_7   = {   6,  70,  34,   82, "7",    1, { TK_NUMBER, "7" } }
SCR_KEY_8   = {  36,  70,  66,   82, "8",    1, { TK_NUMBER, "8" } }
SCR_KEY_9   = {  68,  70,  98,   82, "9",    1, { TK_NUMBER, "9" } }
SCR_KEY_PLS = { 100,  70, 130,   82, "+",    1, { TK_OP_PLUS, "+" } }
SCR_KEY_SIN = { 132,  70, 162,   82, "SIN",  1, { TK_FUNC_SIN, "SIN" } }
SCR_KEY_ASN = { 164,  70, 194,   82, "ASN",  1, { TK_FUNC_ASN, "ASIN" } }
SCR_KEY_PGU = { 196,  70, 234,   82, "PGU",  0, { TK_TASK_PGUP } }

LEFT = 0
RIGHT = 1

function Print_Token( token, x, y )
    if( #token > 1 ) then
        print( string.format( "%d, %d %f", #token, token[1], token[2] ), x, y )
    else
        print( string.format( "%d, %d", #token, token[1] ), x, y )
    end
end

function Print_Tokens( tokens, x, y )
    -- Print Tokens
    for idx = 1, #tokens, 1
    do 
        Print_Token( tokens[idx], x, y + (8*idx) )
    end
end

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

function Is_Operator( token )
    if ( ( token[1] == TK_OP_PLUS ) or
         ( token[1] == TK_OP_MINUS ) or
         ( token[1] == TK_OP_TIMES ) or
         ( token[1] == TK_OP_DIV ) or
         ( token[1] == TK_OP_POWER ) or
         ( token[1] == TK_OP_LPAR ) or 
         ( token[1] == TK_OP_RPAR ) ) then
        return true
    else
        return false
    end
end

function Is_Function( token )
    if ( ( token[1] == TK_FUNC_TAN ) or
         ( token[1] == TK_FUNC_ATN ) or
         ( token[1] == TK_FUNC_SIN ) or
         ( token[1] == TK_FUNC_ASN ) or
         ( token[1] == TK_FUNC_COS ) or
         ( token[1] == TK_FUNC_ACS ) ) then
        return true
    else
        return false
    end
end

function Is_Char_Number( value )
    if ( ( value == "." ) or
         ( value == "0" ) or
         ( value == "1" ) or
         ( value == "2" ) or
         ( value == "3" ) or
         ( value == "4" ) or
         ( value == "5" ) or
         ( value == "6" ) or
         ( value == "7" ) or
         ( value == "8" ) or
         ( value == "9" ) ) then
            return true
    else
        return false
    end
end

function Print( text, cx, cy, color )
    print( text, cx, cy, color ) 
end

function Tokenize( input_str )
    tokens = {}
    working_str = ""
    working_tk  = nil

    -- Iterate over each character in the string
    for idx = 1, #input_str, 1 
    do

        -- Check if character is parenthesis
        if ( string.sub( input_str, idx, idx ) == "(" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == TK_FUNC_UNK ) then
                table.insert( tokens, { String_To_Function( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_LPAR } )

        elseif ( string.sub( input_str, idx, idx ) == ")" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == TK_FUNC_UNK ) then
                table.insert( tokens, { String_To_Function( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_RPAR } )

        -- Check if character is an operator
        elseif ( string.sub( input_str, idx, idx ) == "+" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == TK_FUNC_UNK ) then
                table.insert( tokens, { String_To_Function( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_PLUS } )

        elseif( string.sub( input_str, idx, idx ) == "-" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == TK_FUNC_UNK ) then
                table.insert( tokens, { String_To_Function( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_MINUS } )

        elseif( string.sub( input_str, idx, idx ) == "x" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == TK_FUNC_UNK ) then
                table.insert( tokens, { String_To_Function( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_TIMES } )

        elseif( string.sub( input_str, idx, idx ) == "/" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == TK_FUNC_UNK ) then
                table.insert( tokens, { String_To_Function( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_DIV } )

        elseif( string.sub( input_str, idx, idx ) == "^" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == TK_FUNC_UNK ) then
                table.insert( tokens, { String_To_Function( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_POWER } )
        
        -- Check if number
        elseif( Is_Char_Number( string.sub( input_str, idx, idx ) ) ) then
            if ( working_tk == TK_FUNC_UNK ) then
                -- do nothing
            elseif ( working_tk == nil ) then
                working_tk = TK_NUMBER
            end
            working_str = working_str .. string.sub( input_str, idx, idx )

        -- Blank Character
        elseif ( string.sub( input_str, idx, idx ) == " " ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == TK_FUNC_UNK ) then
                table.insert( tokens, { String_To_Function( working_str ) } )
            end
            working_str = ""
            working_tk  = nil

        -- Character
        elseif ( ( ( string.byte( string.sub( input, idx, idx ) ) >= string.byte( "A" ) ) and
                   ( string.byte( string.sub( input, idx, idx ) ) <= string.byte( "Z" ) ) ) or
                 ( ( string.byte( string.sub( input, idx, idx ) ) >= string.byte( "a" ) ) and
                   ( string.byte( string.sub( input, idx, idx ) ) <= string.byte( "z" ) ) ) )
        then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            elseif ( working_tk == nil ) then
                working_tk = TK_NUMBER
            end
            working_str = working_str .. string.sub( input_str, idx, idx )
        end

    end
   
    -- Cleanup
    if( working_tk == TK_NUMBER ) then
        table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
    end

    return tokens
end

function Process_Operator_Token( token )
    
    num_params = 2
    if ( token[1] == TK_OP_PLUS ) then
        method = function ( opands ) return { TK_NUMBER, ( opands[#opands-1][2] + opands[#opands][2] ) } end
    elseif ( token[1] == TK_OP_MINUS ) then
        method = function ( opands ) return { TK_NUMBER, ( opands[#opands-1][2] - opands[#opands][2] ) } end
    elseif ( token[1] == TK_OP_TIMES ) then
        method = function ( opands ) return { TK_NUMBER, ( opands[#opands-1][2] * opands[#opands][2] ) } end
    elseif ( token[1] == TK_OP_DIV ) then
        method = function ( opands ) return { TK_NUMBER, ( opands[#opands-1][2] / opands[#opands][2] ) } end
    elseif ( token[1] == TK_OP_POWER ) then
        method = function ( opands ) return { TK_NUMBER, math.pow( opands[#opands-1][2], opands[#opands][2] ) } end
    elseif ( token[1] == TK_FUNC_SIN ) then
        method = function ( opands ) return { TK_NUMBER, math.sin( opands[#opands][2] ) } end
    elseif ( token[1] == TK_FUNC_COS ) then
        method = function ( opands ) return { TK_NUMBER, math.sin( opands[#opands][2] ) } end
    elseif ( token[1] == TK_FUNC_TAN ) then
        method = function ( opands ) return { TK_NUMBER, math.tan( opands[#opands][2] ) } end
    end
    return { method, num_params }
end

function Infix2RPN_Shunting_Yard( tokens )

    -- output queue
    output_queue = {}

    -- operator stack
    operator_stack = {}

    -- Iterate over each token
    for idx = 1, #tokens, 1 do

        -- If the token is a number, add to the output queue
        if ( tokens[idx][1] == TK_NUMBER ) then
            table.insert( output_queue, tokens[idx] )

        -- If the token is a left parenthesis
        elseif ( tokens[idx][1] == TK_OP_LPAR ) then
            table.insert( operator_stack, tokens[idx] )
        
        -- If the token is a right parenthesis
        elseif ( tokens[idx][1] == TK_OP_RPAR ) then
            
            while( operator_stack[#operator_stack][1] ~= TK_OP_LPAR )
            do
                table.insert( output_queue, operator_stack[#operator_stack] )
                table.remove( operator_stack, #operator_stack )
            end

            -- dump the left parenthesis
            table.remove( operator_stack, #operator_stack )
            
            -- todo:  Check if function is on top

        -- If the token is an operator, 
        else
            -- If the token is an operator, check the top of the operator stack
            --   1.  The operator is not left parenthesis
            --   2.  The operator has higher precedence than the token operator
            --   3.  The operators are both equal precedence and the current token is left associative
            while( ( #operator_stack > 0 ) and ( operator_stack[#operator_stack][1] ~= TK_OP_LPAR ) and 
                   ( ( Precedence( tokens[idx][1] ) < Precedence( operator_stack[#operator_stack][1] ) ) 
                     or 
                     ( ( Precedence( tokens[idx][1] ) == Precedence( operator_stack[#operator_stack][1] ) ) and Associativity( tokens[idx][1] ) == LEFT ) ) ) 
            do
                table.insert( output_queue, operator_stack[#operator_stack] )
                table.remove( operator_stack, #operator_stack )
            end
            table.insert( operator_stack, tokens[idx])
        end
    end

    -- Pop everything off the operator stack
    while( #operator_stack > 0 ) do
        table.insert( output_queue, operator_stack[#operator_stack] )
        table.remove( operator_stack, #operator_stack )
    end

    return output_queue
end

function Solve_RPN( tokens )

    operand_queue = {}
    
    -- Process all tokens
    while ( #tokens > 0 ) do

        -- Clear off all numbers from the list of tokens
        while( tokens[1][1] == TK_NUMBER ) do
            table.insert( operand_queue, tokens[1] )
            table.remove( tokens, 1 )
        end

        -- Get the next operator
        op = Process_Operator_Token( tokens[1] )
        table.remove( tokens, 1 )

        -- Process with the required arguments
        result = op[1]( operand_queue )

        -- Remove the processed tokens
        for x = 1, op[2], 1 do
            table.remove( operand_queue, #operand_queue )
        end

        -- add result to end of operand queue
        table.insert( operand_queue, result )
    end

    return operand_queue[#operand_queue]
end

function Draw_Terminal( text )
    
    -- for each letter of text, find a sprite
    sprite_list = {}
    table.insert( sprite_list, SPR_START )
    table.insert( sprite_list, SPR_BLANK )

    for i = 1, #text do
       local c = text:sub(i,i)
       
        -- Check if Blank
        if ( c == " " ) then
            table.insert( sprite_list, SPR_BLANK )
        
        -- Check if Parenthesis
        elseif ( c == "(" ) then
            table.insert( sprite_list, SPR_LPARAM )
        elseif ( c == ")" ) then
            table.insert( sprite_list, SPR_RPARAM )

        -- Check if Letter
        elseif ( string.byte(c) >= string.byte("A") and string.byte(c) <= string.byte("Z") ) then
            table.insert( sprite_list, SPR_A + ( string.byte(c) - string.byte("A") ) )
    
        -- Check if Number
        elseif ( string.byte(c) >= string.byte("0") and string.byte(c) <= string.byte("9") ) then
            table.insert( sprite_list, SPR_0 + ( string.byte(c) - string.byte("0") ) )        
    
        -- Check if Operator
        elseif ( c == "+" ) then
            table.insert( sprite_list, SPR_PLUS )
        
        elseif ( c == "-" ) then
            table.insert( sprite_list, SPR_MINUS )
    
        elseif ( c == "x" ) then
            table.insert( sprite_list, SPR_TIMES )
    
        elseif ( c == "/" ) then
            table.insert( sprite_list, SPR_DIVIDE )
    
        elseif ( c == "^" ) then
            table.insert( sprite_list, SPR_POWER )
        
        elseif ( c == '.' ) then
            table.insert( sprite_list, SPR_DOT )
       end
    end
    
    -- Draw Each Sprite
    x = 0
    for key,sprite_id in ipairs( sprite_list ) do 
        spr( sprite_id, 8 * ( 2 + x ), 8 * 4, 0 )
        x = x + 1
    end
end

function Detect_Token( mx, my )

    other_text2 = " matches: "
    other_text3 = " --> " .. string.format( "%d, %d", mx, my )
    KEY_LIST = {}
    table.insert( KEY_LIST, SCR_KEY_CLR )
    table.insert( KEY_LIST, SCR_KEY_0 )
    table.insert( KEY_LIST, SCR_KEY_DOT )
    table.insert( KEY_LIST, SCR_KEY_DIV )
    table.insert( KEY_LIST, SCR_KEY_LPM )
    table.insert( KEY_LIST, SCR_KEY_RPM )
    table.insert( KEY_LIST, SCR_KEY_QUT )

    table.insert( KEY_LIST, SCR_KEY_1 )
    table.insert( KEY_LIST, SCR_KEY_2 )
    table.insert( KEY_LIST, SCR_KEY_3 )
    table.insert( KEY_LIST, SCR_KEY_TIM )
    table.insert( KEY_LIST, SCR_KEY_TAN )
    table.insert( KEY_LIST, SCR_KEY_ATN )
    table.insert( KEY_LIST, SCR_KEY_SLV )

    table.insert( KEY_LIST, SCR_KEY_4 )
    table.insert( KEY_LIST, SCR_KEY_5 )
    table.insert( KEY_LIST, SCR_KEY_6 )
    table.insert( KEY_LIST, SCR_KEY_SUB )
    table.insert( KEY_LIST, SCR_KEY_COS )
    table.insert( KEY_LIST, SCR_KEY_ACS )
    table.insert( KEY_LIST, SCR_KEY_PGD )

    table.insert( KEY_LIST, SCR_KEY_7 )
    table.insert( KEY_LIST, SCR_KEY_8 )
    table.insert( KEY_LIST, SCR_KEY_9 )
    table.insert( KEY_LIST, SCR_KEY_PLS )
    table.insert( KEY_LIST, SCR_KEY_SIN )
    table.insert( KEY_LIST, SCR_KEY_ASN )
    table.insert( KEY_LIST, SCR_KEY_PGU )

    -- check the bounds
    output = nil
    for idx = 1, #KEY_LIST, 1 do
        if ( ( mx >= KEY_LIST[idx][1] ) and ( my >= KEY_LIST[idx][2] ) and ( mx <= KEY_LIST[idx][3] ) and ( my <= KEY_LIST[idx][4] ) ) then
            other_text2 = other_text2 .. string.format( "%d [%s], ", idx, KEY_LIST[idx][5] )
            output = KEY_LIST[idx][7]
            break
        end
    end
    print( other_text2, 8*2, 8*6 )
    print( other_text3, 8*2, 8*7 )
    return output
end

function TIC()

    -- clear screen
    cls()

   map( 0, 0, 30, 17 )

    -- Check the Mouse input
    other_text = "$> "
    mx,my,md = mouse()
    if ( ( md == true ) and ( CURSOR_LOCK == false ) ) then
        token = Detect_Token( mx, my )
        
        if ( token == nil ) then
            -- do nothing
        elseif ( token[1] == TK_TASK_QUIT ) then
            exit()
        elseif ( token[1] == TK_TASK_SOLVE ) then

            -- Tokenize the input string
            infix_tokens = Tokenize( console_text )
        
            -- Convert to RPN
            local rpn_tokens = Infix2RPN_Shunting_Yard( infix_tokens )

            -- Compute the result
            local res = Solve_RPN( rpn_tokens )
            console_text = string.format( "%d", res[2] )
            CURSOR_LOCK = true

        elseif ( token[1] == TK_TASK_CLR ) then
            console_text = ""
            CURSOR_LOCK = true
            other_text = other_text .. "CLS"

        elseif ( token[1] == TK_NUMBER ) then
            console_text = console_text .. token[2]
            CURSOR_LOCK = true
            other_text = other_text .. "NUM: " .. token[2]

        elseif ( Is_Operator( token ) ) then
            console_text = console_text .. token[2]
            CURSOR_LOCK = true
            other_text = other_text .. "OP: " .. token[2]

        elseif ( Is_Function( token ) ) then
            console_text = console_text .. token[2]
            CURSOR_LOCK = true
            other_text = other_text .. "FUNC: " .. token[2]

        else
            -- do nothing for the moment
        end
    elseif ( ( md == false ) and ( CURSOR_LOCK == true ) ) then
        CURSOR_LOCK = false
    end

    Draw_Terminal( console_text )
    print( other_text, 8*2, 8*5 )
    
end

-- <TILES>
-- 000:0011110000111100001111000011110000111100001111000011110000111100
-- 001:0000000000000000111111111111111111111111111111110000000000000000
-- 002:0011110000111100111111111111111111111111111111110011110000111100
-- 003:0000000000000000001111110011111100111111001111110011110000111100
-- 004:0000000000000000111111001111110011111100111111000011110000111100
-- 005:0011110000111100001111110011111100111111001111110000000000000000
-- 006:0011110000111100111111001111110011111100111111000000000000000000
-- 007:0011110000111100001111110011111100111111001111110011110000111100
-- 008:0011110000111100111111001111110011111100111111000011110000111100
-- 009:0000000000000000111111111111111111111111111111110011110000111100
-- 010:0011110000111100111111111111111111111111111111110000000000000000
-- 016:0000000000555500050005500500505005050050055000500055550000000000
-- 017:0000000000055000005050000000500000005000000050000055555000000000
-- 018:0000000000555500050000500000005000555500055000000555555000000000
-- 019:0000000000555500050000500000005000055550050000500055550000000000
-- 020:0000000005000500050005000500050000555500000005000000050000000000
-- 021:0000000005555550050000000555550000000050050000500555555000000000
-- 022:0000000005555550050000000500000005555550050000500555555000000000
-- 023:0000000005555550050000500500005000000050000000500000005000000000
-- 024:0000000000555500050000500555555005000050050000500055550000000000
-- 025:0000000000555500050000500500005000555550000000500000005000000000
-- 026:0000000000000000000000000000000000000000000005500000055000000000
-- 032:0000000000555500050000500500005005555550050000500500005000000000
-- 033:0000000005555500050000500555550005000050050000500555550000000000
-- 034:0000000000555500050000500500000005000000050000500055550000000000
-- 035:0000000005555000050005000500005005000050050005000555500000000000
-- 036:0000000005555550050000500555500005000000050000500555555000000000
-- 037:0000000005555550050000500500000005555500050000000500000000000000
-- 038:0000000000555500050000500500000005005550050000500055550000000000
-- 039:0000000005000050050000500555555005000050050000500500005000000000
-- 040:0000000000555550000050000000500000005000000050000055555000000000
-- 041:0000000000555550000050000000500000005000005050000055500000000000
-- 042:0000000005000500050005000500550005550000050055000500050000000000
-- 043:0000000005000000050000000500000005000000050000000555550000000000
-- 044:0000000005505500050505000505050005050500050505000500050000000000
-- 045:0000000005000050055000500505005005005050050005500500005000000000
-- 046:0000000000555500050000500500005005000050050000500055550000000000
-- 047:0000000005555500050000500500005005555500050000000500000000000000
-- 048:0000000000555500050000500500005005005050050005000055505000000000
-- 049:0000000005555500050000500500005005555500050005500500005000000000
-- 050:0000000000555500050000500500000000555500000000500555550000000000
-- 051:0000000005555500050505000005000000050000000500000005000000000000
-- 052:0000000005500550050000500500005005000050050000500055550000000000
-- 053:0000000005000050050000500050050000500500000550000005500000000000
-- 054:0000000005000500050005000505050005050500050505000055500000000000
-- 055:0000000005505500005050000005000000050000005050000550550000000000
-- 056:0000000005000500050005000055500000050000000500000005000000000000
-- 057:0000000005555500050005000000500000050000005005000555550000000000
-- 064:0000000000055000000550000555555005555550000550000005500000000000
-- 065:0000000000000000000000000555555005555550000000000000000000000000
-- 066:0000000000000550000055000005500000550000055000000500000000000000
-- 067:0000000005000050005005000005500000055000005005000500005000000000
-- 068:0000000000000000000550000050050000500500050000500500005000000000
-- 069:000000000aa0000000aa0000000aa000000aa00000aa00000aa0000000000000
-- 070:0000000000055000005500000050000000500000005500000005500000000000
-- 071:0000000000550000000550000000500000005000000550000055000000000000
-- 072:0000000000050000005550000505050000050000000500000005000000000000
-- 073:0000000000050000000500000005000005050500005550000005000000000000
-- </TILES>

-- <MAP>
-- 000:301010101010101010101010101010101010101010101010101010101040301010101010101010101010101010101010101010101010101010101040000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 001:00b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b10000b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 002:00b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b10000b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 003:00b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b10000b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 004:00b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b10000b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 005:00b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b10000b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 006:00b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b10000b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 007:00b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b10000b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 008:701010109010101090101010901010109010101090101010901010101080701010109010101090101010901010109010101090101010901010101080000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 009:00b171b100b081b000b091b000b104b1002382d2000223d200f262b1840000b1b1b100b0b1b000b0b1b000b1b1b100b1b1b100b1b1b100f262b18400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 010:701010102010101020101010201010102010101020101010201010101080701010102010101020101010201010102010101020101010201010101080000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 011:00b141b100b051b000b061b000b114b10022e223000222d200f262b1940000b1b1b100b0b1b000b0b1b000b1b1b100b1b1b100b1b1b100f262b19400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 012:701010102010101020101010201010102010101020101010201010101080701010102010101020101010201010102010101020101010201010101080000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 013:00b111b100b021b000b031b000b134b1003302d2000233d20023e2b2530000b1b1b100b0b1b000b0b1b000b1b1b100b1b1b100b1b1b10023e2b25300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 014:701010102010101020101010201010102010101020101010201010101080701010102010101020101010201010102010101020101010201010101080000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 015:0022b21300b101b100b1a1b100b124b100b164b100b174b100034382330000a3b1a300b1b1b100b1b1b100b1b1b100b1b1b100b1b1b1000343823300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 016:50101010a0101010a0101010a0101010a0101010a0101010a0101010106050101010a0101010a0101010a0101010a0101010a0101010a01010101060000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 017:000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 132:000000000000000000000000000000000000000000000000000000000000000070707070707000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
-- 133:707070707070707070707070707070707070707070707070707070707070707070707070707070000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 134:707070707070707070707070707070707070707070707070707070707070707070707070707070000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- 135:707070707070707070707070707070707070707070707070707070707070707070707070700000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007070
-- </MAP>

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

