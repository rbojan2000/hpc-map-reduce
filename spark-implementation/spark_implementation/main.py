from pyspark.sql import SparkSession, DataFrame
from pyspark.sql.functions import explode, split, col, regexp_replace, lower
from timeit import default_timer as timer
from spark_implementation.paths import ANNA_KARENINA_TXT_PATH

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
    

def main():
    spark =  SparkSession.builder \
        .appName("word_count") \
        .master("local[*]") \
        .getOrCreate()

    n = 100
    
    start = timer()
    counted_words = word_count(spark, str(ANNA_KARENINA_TXT_PATH), n)
    end = timer()
    print(f"Word count time: {end - start}")

    counted_words.show(10)
    spark.stop()

if __name__ == "__main__":
    main()
