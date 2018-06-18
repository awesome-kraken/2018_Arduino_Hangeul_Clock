
def hi() :
    number_list = []

    while True :
        n = int( input() )

        if n == 0 :
            break
        else :
            if n > 18 :
                number_list.append( n - 1 - 18 )
            else :
                number_list.append(n-1)

        if len( number_list ) == 4 :
            break

    i = 18
    m = 0
    j = len( number_list ) - 1

    while i > 0 :

        if i == number_list[j] :
            m = m | 1
            j = j - 1

            if j == -1 :
                m = m << i
                break
            
        m = m << 1

        i = i - 1

    print( m )


while True :
    hi()
