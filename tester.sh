#!/usr/bin/env bash

# --- CONFIG ---
PHILO_BIN=./philo_bonus

# Valgrind memcheck flags
MEMCHECK_FLAGS="--leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all --fair-sched=yes"

# Valgrind helgrind flags
HELGRIND_FLAGS="--tool=helgrind --trace-children=yes --fair-sched=yes"

# Timeout pour les cas "no death"
TIMEOUT=5

# Logs
MEMCHECK_LOG="memcheck.log"
HELGRIND_LOG="helgrind.log"
OUTPUT_LOG="output.log"

# --- TEST CASES ---
# Format: "ARGS|EXPECTATION|NODEATH"
CASES=(
    "1 800 200 200|should die at ~800ms|0"
    "5 800 200 200|no one should die|1"
    "5 800 200 200 7|no one should die, stop after 7 meals|0"
    "4 410 200 200|no one should die|1"
    "4 310 200 100|should die at ~310ms|0"
    "2 310 200 100|should die at ~310ms|0"
    "200 310 200 100|should die at ~310ms|0"
)

# --- CLEAN LOGS ---
> "$MEMCHECK_LOG"
> "$HELGRIND_LOG"
> "$OUTPUT_LOG"

# --- STEP 1 : Run without valgrind ---
echo "==============================="
echo " STEP 1: Running tests without Valgrind"
echo "==============================="

for case in "${CASES[@]}"; do
    args="$(echo "$case" | cut -d'|' -f1)"
    expectation="$(echo "$case" | cut -d'|' -f2)"
    nodeath="$(echo "$case" | cut -d'|' -f3)"

    # Affichage du test dans le log et à l'écran
    echo >> "$OUTPUT_LOG"
    echo "===============================" | tee -a "$OUTPUT_LOG"
    echo "▶ Test: $args" | tee -a "$OUTPUT_LOG"
    echo "   Expectation: $expectation" | tee -a "$OUTPUT_LOG"

    # Exécution de ./philo
    if [[ "$nodeath" == "1" ]]; then
        timeout $TIMEOUT $PHILO_BIN $args 2>&1 | tee -a "$OUTPUT_LOG"
    else
        $PHILO_BIN $args 2>&1 | tee -a "$OUTPUT_LOG"
    fi

    # Vérification death sur les dernières lignes du log
    if tail -n 20 "$OUTPUT_LOG" | grep -q "died"; then
        if [[ "$nodeath" == "1" ]]; then
            echo "❌ Unexpected death detected!" | tee -a "$OUTPUT_LOG"
        else
            echo "✅ Death detected as expected" | tee -a "$OUTPUT_LOG"
        fi
    else
        if [[ "$nodeath" == "1" ]]; then
            echo "✅ No death as expected" | tee -a "$OUTPUT_LOG"
        else
            echo "❌ No death detected, but expected one!" | tee -a "$OUTPUT_LOG"
        fi
    fi
done


# --- STEP 2 : Run with Valgrind Memcheck (NODEATH=0 only) ---
echo
echo "==============================="
echo " STEP 2: Running tests with Valgrind Memcheck (NODEATH=1 only)"
echo "   (logs in $MEMCHECK_LOG)"
echo "==============================="

for case in "${CASES[@]}"; do
    IFS='|' read -r args expectation nodeath <<< "$case"

    if [[ "$nodeath" == "0" ]]; then
        echo >> "$MEMCHECK_LOG"
        echo "▶ Test: $args" >> "$MEMCHECK_LOG"
        echo "   Expectation: $expectation" >> "$MEMCHECK_LOG"

        valgrind $MEMCHECK_FLAGS $PHILO_BIN $args >> "$MEMCHECK_LOG" 2>&1
    fi
done

# --- STEP 3 : Run with Valgrind Helgrind (NODEATH=0 only) ---
echo
echo "==============================="
echo " STEP 3: Running tests with Valgrind Helgrind (NODEATH=1 only)"
echo "   (logs in $HELGRIND_LOG)"
echo "==============================="

for case in "${CASES[@]}"; do
    IFS='|' read -r args expectation nodeath <<< "$case"

    if [[ "$nodeath" == "0" ]]; then
        echo >> "$HELGRIND_LOG"
        echo "▶ Test: $args" >> "$HELGRIND_LOG"
        echo "   Expectation: $expectation" >> "$HELGRIND_LOG"

        valgrind $HELGRIND_FLAGS $PHILO_BIN $args >> "$HELGRIND_LOG" 2>&1
    fi
done
