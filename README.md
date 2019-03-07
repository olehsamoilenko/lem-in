# lem-in
Допустим, есть k путей длинами l1, l2, l3, ... , lk
Запустим по i-тому пути длиной li муравьев в количестве Ni.
По параллельному j-тому пути длиной lj = li+x стоило бы запустить Ni-x муравьев,
так как они достигнут финиша одновременно, а значит, количество муравьев,
запущенное по j-тому пути равно nj = ni-(lj-li).
Суммарное количество муравьев N = n1+n2+...+nk = ni-(l1-li)+ni-(l2-li)+...+ni-(lk-li) =
= k*ni-(l1+l2+...+lk)+k*li = k(ni+li)-(l1+l2+...+lk)
Отсюда количество муравьев, которое следует запустить по i-тому пути равно:
ni = (N+l1+l2+...lk)/k-li = (N+L)/k-li

Несложно понять, что количетсво ходов для перемещения всех муравьев из старта на финиш
с помощью выбранной группы путей равняется:
t = ni+(li-1) = (N+L)/k-li+li-1 = (N+L)/k-1
(+1, если остаются лишние муравьи, то есть (N+L)%k != 0)

http://graphonline.ru/?graph=yKeYUYwBJdBluVcy complicated
http://graphonline.ru/?graph=gTvvhJVhAMXwDzCk double_ways
http://graphonline.ru/?graph=pPZVUCqghhZDquNm flow_two_ways_different_length
http://graphonline.ru/?graph=GpbTWFxsKDcsfohr two_ways_connected
http://graphonline.ru/?graph=vFrwpEhoDmIrKpzY two_ways_collision
http://graphonline.ru/?graph=zPIJdNYGwHRnsvtL one_way_through_three
http://graphonline.ru/?graph=bWkgLznYQjDhMRop three_equal_ways_connected
http://graphonline.ru/?graph=YsiKUZYtpkmkCpRB subject_one_way_through_two
http://graphonline.ru/?graph=clPaAbFRJwOTUEzt flow_three_ways_different_length
http://graphonline.ru/?graph=AfQvrfsNTYDmBCnq salavat
