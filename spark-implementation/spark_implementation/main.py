from pyspark.sql import SparkSession, DataFrame
from pyspark.sql.functions import explode, split, col, lower, regexp_replace
import time

def word_count(spark: SparkSession, file_path: str, n: int) -> DataFrame:
    df1 = spark.read.text(file_path)

    for _ in range(n-1):
        df1 = df1.union(spark.read.text(file_path))


    cleaned_text = df1.select(
        lower(
            regexp_replace(
                col("value"), "[/?.!,:;\"\'\\-]", ""
            )
        )
        .alias("value")
    )

    words = cleaned_text \
        .select( \
            explode(split(col("value"), "\\s+")) \
            .alias("word")
        )

    words_filtered = words.filter(col("word") != "")

    word_count = words_filtered \
        .groupBy("word") \
        .count()
        
    return word_count

if __name__ == "__main__":
    file_path = "../input-text/Anna-Karenina.txt"
    n = 1
    
    spark = SparkSession.builder \
        .appName("WordCount") \
        .master("local[*]") \
        .getOrCreate()
    
    start_time = time.time()
    result = word_count(spark, file_path, n)
    end_time = time.time()

    print(f"Word count computation completed in {end_time - start_time:.2f} seconds")
    
    result.show()

    spark.stop()
