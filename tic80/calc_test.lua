-- title:  calc_test.lua
-- author: Marvin Smith
-- desc:   Simple calculator solver
-- script: lua


luaunit = require('luaunit')



--input_str = "3 + 4 x 2"

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


SPR_BLANK  = 27
SPR_A      = 32
SPR_Z      = 57
SPR_0      = 16
SPR_9      = 25
SPR_DOT    = 26
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
        print( string.format( "%d, %d %f", #token, token[1], token[2] ) )
    else
        print( string.format( "%d, %d", #token, token[1] ) )
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
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_LPAR } )

        elseif ( string.sub( input_str, idx, idx ) == ")" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_RPAR } )

        -- Check if character is an operator
        elseif ( string.sub( input_str, idx, idx ) == "+" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_PLUS } )

        elseif( string.sub( input_str, idx, idx ) == "-" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_MINUS } )

        elseif( string.sub( input_str, idx, idx ) == "x" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_TIMES } )

        elseif( string.sub( input_str, idx, idx ) == "/" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_DIV } )

        elseif( string.sub( input_str, idx, idx ) == "^" ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
            table.insert( tokens, { TK_OP_POWER } )
        
        -- Check if number
        elseif( Is_Char_Number( string.sub( input_str, idx, idx ) ) ) then
            if ( working_tk == nil ) then
                working_tk = TK_NUMBER
            end
            working_str = working_str .. string.sub( input_str, idx, idx )

        -- Blank Character
        elseif ( string.sub( input_str, idx, idx ) == " " ) then
            if( working_tk == TK_NUMBER ) then
                table.insert( tokens, { TK_NUMBER, tonumber( working_str ) } )
            end
            working_str = ""
            working_tk  = nil
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

function spr( value, x, y, z ) 
    print( "%s", value )
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

        -- Check if Letter
        elseif ( c >= "A" and c <= "Z" ) then
            c = 0
        
        -- Check if Parenthesis
        elseif ( c == "(" ) then
            table.insert( sprite_list, SPR_LPARAM )
        elseif ( c == ")" ) then
            table.insert( sprite_list, SPR_RPARAM )
    
        -- Check if Number
        elseif ( string.byte(c) >= string.byte("0") and string.byte(c) <= string.byte("9") ) then
            table.insert( sprite_list, SPR_0 + ( string.byte(c) - string.byte("0") ) )        
    
    --    -- Check if Operator
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
            Print_Tokens( rpn_tokens, 16, 2 )
      
            -- Compute the result
            --result = Solve_RPN( rpn_tokens )
            --console_text = string.format( "%d", result[2] )

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
    print( string.format( "> LOCK: %s", CURSOR_LOCK ), 8*2, 8*8 )
end

function testTokenize01()

    -- Test the tokenize function
    local input_str = "3 + 4 - 2.3"
    local tokens = Tokenize( input_str )
    luaunit.assertEquals( #tokens, 5 )
end

function testTokenize02()
    -- Test the tokenize function

    local input_str = "3+4-2.3"
    local tokens = Tokenize( input_str )
    Print_Tokens( tokens, 16, 32 )

    luaunit.assertEquals( #tokens, 5 )
    luaunit.assertAlmostEquals( tokens[1][2], 3, 0.1 )
    luaunit.assertEquals( tokens[2][1], TK_OP_PLUS )
    luaunit.assertAlmostEquals( tokens[3][2], 4, 0.1 )
    luaunit.assertEquals( tokens[4][1], TK_OP_MINUS )
    luaunit.assertAlmostEquals( tokens[5][2], 2.3, 0.1 )
end

function testInfix2RPN_Shunting_Yard()
    local input_str = "3 + 4.3 x 7"
    local tokens = Tokenize( input_str )
    local result = Infix2RPN_Shunting_Yard( tokens )
    luaunit.assertEquals( #result, 5 )

    local input_str = "3 + 4 x 2 / ( 1 - 5 ) ^ 2 ^ 3"
    tokens = Tokenize( input_str )
    result = Infix2RPN_Shunting_Yard( tokens )
end

function testSolve_RPN_01()
    local input_str = "3 + 4.3 x 7"
    tokens = Tokenize( input_str )
    rpn_tokens = Infix2RPN_Shunting_Yard( tokens )
    result = Solve_RPN( rpn_tokens )
    luaunit.assertAlmostEquals( result[2], 33.1, 0.1 )
end

function testSolve_RPN_02()
    local input_str = "3 + 4 x 2 / ( 1 - 5 ) ^ 2 ^ 3"
    tokens = Tokenize( input_str )
    rpn_tokens = Infix2RPN_Shunting_Yard( tokens )
    result = Solve_RPN( rpn_tokens )
    luaunit.assertAlmostEquals( result[2], 3.0001, 0.1 )
end

function testSolve_RPN_03()

    local console_text = "3+4x2"

    -- Tokenize the input string
    infix_tokens = Tokenize( console_text )
        
    -- Convert to RPN
    local rpn_tokens = Infix2RPN_Shunting_Yard( infix_tokens )
    Print_Tokens( rpn_tokens, 16, 2 )

    -- Compute the result
    result = Solve_RPN( rpn_tokens )
    console_text = string.format( "%d", result[2] )
    luaunit.assertAlmostEquals( result[2], 11, 0.1 )
    print(console_text)
end

os.exit( luaunit.LuaUnit.run() )

