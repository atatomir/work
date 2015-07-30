var n:longint;
begin
  read(n);
  if n <= 4 then write('few') else
  if n <= 9 then write('several') else
  if n <= 19 then write('pack') else
  if n <= 49 then write('lots') else
  if n <= 99 then write('horde') else
  if n <= 249 then write('throng') else
  if n <= 499 then write('swarm') else
  if n <= 999 then write('zounds') else
                 write('legion');

end.