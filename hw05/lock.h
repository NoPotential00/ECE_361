/** States in the combination-lock finite-state machine. */
typedef enum {
    LOCKED, /**< No combination digits have been accepted. */
    GOT1,   /**< The first digit is correct. */
    GOT2,   /**< The first two digits are correct. */
    OPEN,   /**< The complete combination was entered. */
    N_STATES /**< Number of valid states. */
} state_t;

/** Events that can be applied to the lock. */
typedef enum {
    E_RIGHT,   /**< The next entered digit is correct. */
    E_WRONG,   /**< The entered digit is incorrect. */
    E_CLOSE,   /**< The door is closed. */
    E_TIMEOUT, /**< The entry timer expires. */
    N_EVENTS   /**< Number of valid events. */
} event_t;

/** Physical action produced by a transition. */
typedef enum {
    A_UNDEFINED, /**< No action was specified. */
    A_NONE,      /**< Do nothing. */
    A_UNLOCK,    /**< Unlock the door. */
    A_LOCK,      /**< Lock the door. */
    A_BEEP,      /**< Sound the error beep. */
    N_ACTIONS    /**< Number of valid actions. */
} action_t;

/** One state-machine table entry. */
typedef struct {
    state_t next;    /**< State reached after the event. */
    action_t action; /**< Action produced by the transition. */
} transition_t;

/** Complete transition table indexed by state and event. */
extern const transition_t lock_table[N_STATES][N_EVENTS];

/**
 * Apply an event to a state using the lock transition table.
 *
 * @param s Current state.
 * @param e Event to apply.
 * @param[out] action Receives the transition action when non-NULL.
 * @return The next state, or @p s when the inputs are out of range.
 */
state_t         lock_step(state_t s, event_t e, action_t *action);

/**
 * Convert an input character into a lock event.
 *
 * Digits are interpreted relative to the current state; `c`/`C` means close
 * and `t`/`T` means timeout. Any other digit is an incorrect digit.
 *
 * @param s Current state.
 * @param c Input character.
 * @return The corresponding event.
 */
int             lock_event(state_t s, char c);

/** @param s State to name. @return Printable state name or "UNKNOWN". */
const char     *state_name(state_t s);

/** @param e Event to name. @return Printable event name or "UNKNOWN". */
const char     *event_name(event_t e);

/** @param a Action to name. @return Printable action name or "UNKNOWN". */
const char     *action_name(action_t a);
