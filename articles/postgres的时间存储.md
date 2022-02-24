# postgres的时间存储



postgresql latest version(14) 所支持的时间日期类型如下：

| Name                                    | Storage Size | Description                           | Low Value        | High Value      | Resolution    |
| --------------------------------------- | ------------ | ------------------------------------- | ---------------- | --------------- | ------------- |
| timestamp [ (p) ] [ without time zone ] | 8 bytes      | both date and time (no time zone)     | 4713 BC          | 294276 AD       | 1 microsecond |
| timestamp [ (p) ] with time zone        | 8 bytes      | both date and time, with time zone    | 4713 BC          | 294276 AD       | 1 microsecond |
| date                                    | 4 bytes      | date (no time of day)                 | 4713 BC          | 5874897 AD      | 1 day         |
| time [ (p) ] [ without time zone ]      | 8 bytes      | time of day (no date)                 | 00:00:00         | 24:00:00        | 1 microsecond |
| time [ (p) ] with time zone             | 12 bytes     | time of day (no date), with time zone | 00:00:00+1559    | 24:00:00-1559   | 1 microsecond |
| interval [ fields ] [ (p) ]             | 16 bytes     | time interval                         | -178000000 years | 178000000 years | 1 microsecond |

对于以上的时间和日期的值在传递给postgresql时都是一个string，pg在取得字段类型后根据类型对字符串进行解析























Refer: https://www.postgresql.org/docs/9.1/datatype-datetime.html