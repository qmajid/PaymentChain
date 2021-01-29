-- Table: public.block

-- DROP TABLE public.block;

CREATE TABLE public.block
(
  block_id integer NOT NULL,
  block_index bigint,
  block_time bigint,
  block_data text,
  CONSTRAINT block_pkey PRIMARY KEY (block_id)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.block
  OWNER TO postgres;

