-- title:  calc_test.lua
-- author: Marvin Smith
-- desc:   Simple calculator solver
-- script: lua


luaunit = require('luaunit')



--input_str = "3 + 4 x 2 / (1 - 5 ) ^2 ^2"

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

function Print_Tokens( tokens )
    -- Print Tokens
    local i=0
    for _, v in ipairs( tokens ) 
    do 
        if( #v > 1 ) then
            print( string.format( "%d, %d %f", #v, v[1], v[2] ) )
        else
            print( string.format( "%d, %d", #v, v[1] ) )
        end
        i = i + 1
    end
end

function Print_Tokens_2( tokens, len )
    for idx = 1, len, 1
    do
        if( #v > 1 ) then
            print( string.format( "%d, %d %f", #v, v[1], v[2] ) )
        else
            print( string.format( "%d, %d", #v, v[1] ) )
        end
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

        print(string.format('Index: %d', idx))
        -- If the token is a number, add to the output queue
        if ( ( #tokens[idx] > 1 ) and ( tokens[idx][1] == TK_NUMBER ) ) then
            table.insert( output_queue, tokens[idx] )
            oque_idx = oque_idx + 1

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
                   ( operator_stack[opstack_idx][1] ~= TK_OP_LPAR ) and 
                   ( ( Precedence( tokens[idx][1] ) > Precedence( operator_stack[opstack_idx][1] ) ) 
                     or 
                     ( ( Precedence( tokens[idx][1] ) == Precedence( operator_stack[opstack_idx][1] ) ) and Associativity( tokens[idx][1] ) == LEFT ) ) ) 
            do
                output_queue[oque_idx] = operator_stack[opstack_idx]
                oque_idx = oque_idx + 1
                operator_stack[opstack_idx] = tokens[idx]
            end
        end
    end

    -- Pop everything off the operator stack
    while( opstack_idx > 0 ) do
        output_queue[oque_idx] = operator_stack[opstack_idx]
        opstack_idx = opstack_idx - 1
    end

    print('AAAA')
    Print_Tokens_2( output_queue, oque_idx )
    print('BBBB')
    Print_Tokens_2( operator_stack, opstack_idx )
    print('End of Method')
    return output_queue
end


function testTokenize()

    local input_str = "3 + 4 - 2.3"
    tokens = Tokenize( input_str )
    luaunit.assertEquals( #tokens, 5 )

end

function testInfix2RPN_Shunting_Yard()
    local input_str = "3 + 4 - 2.3"
    tokens = Tokenize( input_str )
    print('Tokens')
    Print_Tokens( tokens )

    print('Results')
    result = Infix2RPN_Shunting_Yard( tokens )
    Print_Tokens_2( result, #tokens )
end



os.exit( luaunit.LuaUnit.run() )

