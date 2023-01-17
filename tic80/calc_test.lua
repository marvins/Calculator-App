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

function Print_Token( token )
    if( #token > 1 ) then
        print( string.format( "%d, %d %f", #token, token[1], token[2] ) )
    else
        print( string.format( "%d, %d", #token, token[1] ) )
    end
end

function Print_Tokens( tokens )
    -- Print Tokens
    for idx = 1, #tokens, 1
    do 
        Print_Token( tokens[idx] )
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
        elseif( str == "^" ) then
            value = { TK_OP_POWER }
        elseif( str == "(" ) then
            value = { TK_OP_LPAR }
        elseif( str == ")" ) then
            value = { TK_OP_RPAR }
        else
            value = { TK_NUMBER, tonumber(str) }
        end
        table.insert( tokens, value )
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


function testTokenize()
    -- Test the tokenize function

    local input_str = "3 + 4 - 2.3"
    tokens = Tokenize( input_str )
    luaunit.assertEquals( #tokens, 5 )
end

function testInfix2RPN_Shunting_Yard()
    local input_str = "3 + 4.3 x 7"
    tokens = Tokenize( input_str )
    result = Infix2RPN_Shunting_Yard( tokens )
    luaunit.assertEquals( #result, 5 )

    input_str = "3 + 4 x 2 / ( 1 - 5 ) ^ 2 ^ 3"
    tokens = Tokenize( input_str )
    result = Infix2RPN_Shunting_Yard( tokens )
end

function testSolve_RPN_01()
    local input_str = "3 + 4.3 x 7"
    tokens = Tokenize( input_str )
    rpn_tokens = Infix2RPN_Shunting_Yard( tokens )
    result = Solve_RPN( rpn_tokens )
    print( "%d, %d", result[1], result[2] )
    luaunit.assertAlmostEquals( result[2], 30.1, 0.1 )
end

function testSolve_RPN_02()
    local input_str = "3 + 4 x 2 / ( 1 - 5 ) ^ 2 ^ 3"
    tokens = Tokenize( input_str )
    rpn_tokens = Infix2RPN_Shunting_Yard( tokens )
    result = Solve_RPN( rpn_tokens )
    print( "%d, %d", result[1], result[2] )
    luaunit.assertAlmostEquals( result[2], 3.0001, 0.1 )
end


os.exit( luaunit.LuaUnit.run() )

